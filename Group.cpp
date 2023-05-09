//
// Created by user on 07/05/2023.
//

#include "Group.h"

Group::Group(int groupId) : MovieWatcher(groupId),m_members(){
}

StatusType Group::insert(User& user){
    if(!user.setGroup(this))
        return StatusType::FAILURE;
    StatusType result = m_members.insert(&user, user.getId());
    if(result != StatusType::SUCCESS)
        return result;
    m_size++;
    if(!m_isVip && user.isVip())
        m_isVip = true;
    const int* userViews = user.getAllViewsArr();
    for(int i = 0; i < (int)Genre::NONE; i++){
        m_groupWatchHistory[i] += userViews[i];
    }
    return StatusType::SUCCESS;
}

Genre Group::getFavoriteGenre() const{
    int view_count = m_groupWatchHistory[(int)Genre::COMEDY];
    Genre result = Genre::COMEDY;
    if(view_count < m_groupWatchHistory[(int)Genre::DRAMA]){
        view_count = m_groupWatchHistory[(int)Genre::DRAMA];
        result = Genre::DRAMA;
    }
    if(view_count < m_groupWatchHistory[(int)Genre::ACTION]){
        view_count = m_groupWatchHistory[(int)Genre::ACTION];
        result = Genre::ACTION;
    }
    if(view_count < m_groupWatchHistory[(int)Genre::FANTASY]){
        view_count = m_groupWatchHistory[(int)Genre::FANTASY];
        result = Genre::FANTASY;
    }
    return result;
}

void Group::updateGWH(Genre genre){
    m_groupWatchHistory[(int)genre]++;
    m_groupWatchHistory[(int)Genre::NONE]++;
}

void Group::watchMovie(Movie &movie) {
    MovieWatcher::watchMovie(movie);
    m_groupWatchHistory[(int)movie.getMovieGenre()]+= m_size;
    m_groupWatchHistory[(int)Genre::NONE]+= m_size;
}

int Group::getViewsGenre(Genre genre) const {
    return m_watchHistory[(int)genre];
}
Group::~Group() {
    if(m_size == 0)
        return;
    Pair<User*, int>** userArr = nullptr;
    if(!m_members.inOrderScanToArray(userArr))
        throw std::bad_alloc();
    MovieWatcher* base_ptr_user;
    for(int i = 0; i< m_size; i++){
        base_ptr_user = userArr[i]->data();
        remover(base_ptr_user);
    }
    delete[] userArr;
}

/// FIX HERE USER GET ALL VIEWS NEEDS NEW LOGIC

void Group::remove(MovieWatcher *toBeRemoved) {
    const int userComedyViews = m_members.find(toBeRemoved->getId())->data()->getViewsGenre(Genre::COMEDY);
    const int userActionViews = m_members.find(toBeRemoved->getId())->data()->getViewsGenre(Genre::ACTION);
    const int userDramaViews = m_members.find(toBeRemoved->getId())->data()->getViewsGenre(Genre::DRAMA);
    const int userFantasyViews = m_members.find(toBeRemoved->getId())->data()->getViewsGenre(Genre::FANTASY);
    const int userAllViews = m_members.find(toBeRemoved->getId())->data()->getViewsGenre(Genre::NONE);

    m_members.remove(toBeRemoved->getId());

    m_groupWatchHistory[(int)Genre::COMEDY] -= userComedyViews;
    m_groupWatchHistory[(int)Genre::ACTION] -= userActionViews;
    m_groupWatchHistory[(int)Genre::DRAMA] -= userDramaViews;
    m_groupWatchHistory[(int)Genre::FANTASY] -= userFantasyViews;
    m_groupWatchHistory[(int)Genre::NONE] -= userAllViews;
}


