#include "StreamingDBa1.h"


AVLTree<Movie,Movie>& streaming_database::getGenreTree(const Movie& movie) {
    switch (movie.getMovieGenre()) {
        case Genre::COMEDY:
            return m_comedyMovies;
        case Genre::ACTION:
            return m_actionMovies;
        case Genre::DRAMA:
            return m_dramaMovies;
        default:
            return m_fantasyMovies;
    }
}

AVLTree<Movie,Movie>& streaming_database::getGenreTree(const Genre genre) {
    switch (genre) {
        case Genre::COMEDY:
            return m_comedyMovies;
        case Genre::ACTION:
            return m_actionMovies;
        case Genre::DRAMA:
            return m_dramaMovies;
        default:
            return m_fantasyMovies;
    }
}

streaming_database::streaming_database() :  m_moviesByID(), m_moviesByRating(), m_actionMovies(), m_comedyMovies(),
                                            m_dramaMovies(), m_fantasyMovies(){}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <= 0 || views < 0 || genre == Genre::NONE)
        return StatusType::INVALID_INPUT;
    Movie movie = Movie(movieId,genre,views,vipOnly);
    StatusType flag = m_moviesByID.insert(movie,movieId);
    if(flag == StatusType::SUCCESS){
        AVLTree<Movie, Movie>& genreTree = getGenreTree(movie);
        flag = genreTree.insert(movie, movie);
        if(flag == StatusType::SUCCESS){
            flag = m_moviesByRating.insert(movie, movie);
            if(flag == StatusType::SUCCESS)
                return StatusType::SUCCESS;
            genreTree.remove(movie);
        }
        m_moviesByID.remove(movieId);
    }
}

StatusType streaming_database::remove_movie(int movieId)
{

    if(movieId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);
    if(moviePair)
        return StatusType::FAILURE;
    StatusType flag =  m_moviesByRating.remove(moviePair->data());
    if(flag != StatusType::SUCCESS)
        return flag;
    AVLTree<Movie, Movie>& genreTree = getGenreTree(moviePair->data());
    flag = genreTree.remove(moviePair->data());
    if(flag != StatusType::SUCCESS)
        return flag;
    return m_moviesByID.remove(movieId);
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    return m_userTreeByID.insert(User(userId,isVip),userId);
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    return m_userTreeByID.remove(userId);
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    return m_groupTreeByID.insert(Group(groupId),groupId);
}

StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    return m_groupTreeByID.remove(groupId);
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId <= 0 || groupId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<User,int>* userPair = m_userTreeByID.find(userId);
    Pair<Group,int>* groupPair = m_groupTreeByID.find(groupId);
    if(!userPair || !groupPair || userPair->data().isInGroup())
        return StatusType::FAILURE;
    return groupPair->data().insert(userPair->data());
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(userId <= 0 || movieId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<User,int>* userPair = m_userTreeByID.find(userId);
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);

    if(!userPair || !moviePair || (!userPair->data().isVip() && moviePair->data().isVipOnly()))
        return StatusType::FAILURE;
    AVLTree<Movie, Movie>& genreTree = getGenreTree(moviePair->data());
    Movie movie = moviePair->data();
    userPair->data().watchMovie(moviePair->data());
    genreTree.remove(movie);
    genreTree.insert(moviePair->data(),moviePair->data());
    m_moviesByRating.remove(movie);
    m_moviesByRating.insert(moviePair->data(),moviePair->data());
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(movieId <= 0 || groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Pair<Group,int>* groupPair = m_groupTreeByID.find(groupId);
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);
    if(!groupPair || !moviePair || groupPair->data().isempty() || (!groupPair->data().isVip() && moviePair->data().isVipOnly()))
        return StatusType::FAILURE;
    AVLTree<Movie, Movie>& genreTree = getGenreTree(moviePair->data());
    Movie movie = moviePair->data();
    groupPair->data().watchMovie(moviePair->data());
    genreTree.remove(movie);
    genreTree.insert(moviePair->data(),moviePair->data());
    m_moviesByRating.remove(movie);
    m_moviesByRating.insert(moviePair->data(),moviePair->data());
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    AVLTree<Movie, Movie>& genreTree = getGenreTree(genre);
    if(genre == Genre::NONE)
        return (m_fantasyMovies.size() + m_dramaMovies.size() + m_actionMovies.size() + m_comedyMovies.size());
    return genreTree.size();
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(!output)
        return StatusType::INVALID_INPUT;

    Pair<Movie, Movie>** pairArr = nullptr;
    int arr_size;
    if(genre == Genre::NONE){
       if(!m_moviesByRating.inOrderScanToArray(pairArr))
           return StatusType::ALLOCATION_ERROR;
        arr_size = m_moviesByRating.size();
    }else{
        AVLTree<Movie, Movie>& genreTree = getGenreTree(genre);
        if(!genreTree.inOrderScanToArray(pairArr))
            return StatusType::ALLOCATION_ERROR;
        arr_size = genreTree.size();
    }
    if(arr_size == 0) {
        delete[] pairArr;
        return  StatusType::FAILURE;
    }
    try{
        int* result = new int[arr_size];
        for(int i = 0; i < arr_size; i++){
            result[i] = pairArr[i]->data().getMovieId();
        }
        output = result;
    }catch(...){
        delete[] pairArr;
        return StatusType::ALLOCATION_ERROR;
    }
    delete[] pairArr;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<User,int>* userPair = m_userTreeByID.find(userId);
    if(!userPair)
        return StatusType::FAILURE;
    return userPair->data().getNumOfViews(genre);
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if(userId <= 0 || movieId <= 0 || (rating < 0 || rating > 100))
        return StatusType::INVALID_INPUT;
    Pair<User,int>* userPair = m_userTreeByID.find(userId);
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);
    if(!userPair || !moviePair || (!userPair->data().isVip() && moviePair->data().isVipOnly()))
        return StatusType::FAILURE;
    moviePair->data().addRating(rating);
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<Group,int>* groupPair = m_groupTreeByID.find(groupId);
    if(!groupPair)
        return StatusType::FAILURE;
    Genre genre = groupPair->data().getFavoriteGenre();
    AVLTree<Movie, Movie>& genreTree = getGenreTree(genre);
    return genreTree.select(genreTree.size())->data().getMovieId();
}


