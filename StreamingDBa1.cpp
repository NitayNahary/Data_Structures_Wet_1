#include "StreamingDBa1.h"


streaming_database::streaming_database() :  m_moviesByID(),m_groupTreeByID(),m_userTreeByID(), m_genreMovies(){}

StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <= 0 || views < 0 || genre == Genre::NONE)
        return StatusType::INVALID_INPUT;
    Movie movie = Movie(movieId,genre,views,vipOnly);
    StatusType flag = m_moviesByID.insert(movie,movieId);
    if(flag != StatusType::SUCCESS)
        return flag;
    flag = m_genreMovies[(int)genre].insert(movie, movie);
    if(flag == StatusType::SUCCESS){
        flag = m_genreMovies[(int)Genre::NONE].insert(movie, movie);
        if(flag != StatusType::SUCCESS){
            m_genreMovies[(int)genre].remove(movie);
        }
    }else{
        m_moviesByID.remove(movieId);
    }
    if(!m_genreMovies[(int)genre].empty())
        m_genreHotMovies[(int)genre] = m_genreMovies[(int)genre].select(1)->data().getMovieId();
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);
    if(!moviePair)
        return StatusType::FAILURE;
    int genre = (int)(moviePair->data().getMovieGenre());
    StatusType flag =  m_genreMovies[(int)Genre::NONE].remove(moviePair->data());
    if(flag != StatusType::SUCCESS)
        return flag;
    flag = m_genreMovies[genre].remove(moviePair->data());
    if(flag != StatusType::SUCCESS)
        return flag;
    if(!m_genreMovies[genre].empty())
        m_genreHotMovies[genre] = m_genreMovies[genre].select(1)->data().getMovieId();
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
    Pair<User,int>* userPair = m_userTreeByID.find(userId);
    if(!userPair)
        return StatusType::FAILURE;
    StatusType res = userPair->data().destroy();
    if(res != StatusType::SUCCESS)
        return res;
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
    Pair<Group,int>* groupPair = m_groupTreeByID.find(groupId);
    if(!groupPair)
        return StatusType::FAILURE;
    StatusType res = groupPair->data().destroy();
    if(res != StatusType::SUCCESS)
        return res;
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

    Movie movie = moviePair->data();
    int movieGenre = (int)moviePair->data().getMovieGenre();
    StatusType resFlag;
    resFlag = m_genreMovies[movieGenre].remove(movie);
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    resFlag =m_genreMovies[(int)Genre::NONE].remove(movie);
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    userPair->data().watchMovie(moviePair->data());
    resFlag = m_genreMovies[movieGenre].insert(moviePair->data(),moviePair->data());
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    if(!m_genreMovies[movieGenre].empty())
        m_genreHotMovies[movieGenre] = m_genreMovies[movieGenre].select(1)->data().getMovieId();
    return m_genreMovies[(int)Genre::NONE].insert(moviePair->data(),moviePair->data());
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(movieId <= 0 || groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Pair<Group,int>* groupPair = m_groupTreeByID.find(groupId);
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);
    if(!groupPair || !moviePair || groupPair->data().isEmpty() || (!groupPair->data().isVip() && moviePair->data().isVipOnly()))
        return StatusType::FAILURE;
    int movieGenre = (int)moviePair->data().getMovieGenre();
    Movie movie = moviePair->data();
    StatusType resFlag;
    resFlag = m_genreMovies[movieGenre].remove(movie);
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    resFlag = m_genreMovies[(int)Genre::NONE].remove(movie);
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    groupPair->data().watchMovie(moviePair->data());
    resFlag = m_genreMovies[movieGenre].insert(moviePair->data(),moviePair->data());
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    if(!m_genreMovies[movieGenre].empty())
        m_genreHotMovies[movieGenre] = m_genreMovies[movieGenre].select(1)->data().getMovieId();
    return m_genreMovies[(int)Genre::NONE].insert(moviePair->data(),moviePair->data());
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    return (m_genreMovies[(int)genre].size());
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(!output)
        return StatusType::INVALID_INPUT;
    Pair<Movie, Movie>** pairArr = nullptr;
    int arr_size = m_genreMovies[(int)genre].size();
    if(arr_size == 0)
        return StatusType::FAILURE;
    if(!m_genreMovies[(int)genre].inOrderScanToArray(pairArr))
        return StatusType::ALLOCATION_ERROR;
    for(int i = 0; i < arr_size; i++){
        output[i] = pairArr[i]->data().getMovieId();
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
    return userPair->data().getViewsGenre(genre);
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if(userId <= 0 || movieId <= 0 || (rating < 0 || rating > 100))
        return StatusType::INVALID_INPUT;
    Pair<User,int>* userPair = m_userTreeByID.find(userId);
    Pair<Movie,int>* moviePair = m_moviesByID.find(movieId);
    if(!userPair || !moviePair || (!userPair->data().isVip() && moviePair->data().isVipOnly()))
        return StatusType::FAILURE;
    StatusType resFlag;
    int movieGenre = (int)moviePair->data().getMovieGenre();
    resFlag = m_genreMovies[movieGenre].remove(moviePair->data());
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    resFlag = m_genreMovies[(int)Genre::NONE].remove(moviePair->data());
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    moviePair->data().addRating(rating);
    resFlag = m_genreMovies[movieGenre].insert(moviePair->data(),moviePair->data());
    if(resFlag != StatusType::SUCCESS)
        return resFlag;
    if(!m_genreMovies[movieGenre].empty())
        m_genreHotMovies[movieGenre] = m_genreMovies[movieGenre].select(1)->data().getMovieId();
    return  m_genreMovies[(int)Genre::NONE].insert(moviePair->data(),moviePair->data());
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0)
        return StatusType::INVALID_INPUT;
    Pair<Group,int>* groupPair = m_groupTreeByID.find(groupId);
    if(!groupPair || groupPair->data().isEmpty())
        return StatusType::FAILURE;
    Genre genre = groupPair->data().getFavoriteGenre();
    if(m_genreMovies[(int)genre].empty())
        return StatusType::FAILURE;
    return m_genreHotMovies[(int)genre];
}