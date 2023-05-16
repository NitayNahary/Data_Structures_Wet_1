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
    if((user.isVip()))
        m_isVip++;
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
        result = Genre::FANTASY;
    }
    return result;
}

void Group::updateGroupGenre(Genre genre){
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
StatusType Group::destroy(){
    if(m_size == 0)
        return StatusType::SUCCESS;
    Pair<User*, int>** userArr = nullptr;
    if(!m_members.inOrderScanToArray(userArr))
        return StatusType::ALLOCATION_ERROR;
    StatusType flag = StatusType::SUCCESS;
    for(int i = 0; i< m_size && flag == StatusType::SUCCESS; i++){
        flag = updateOnRemove(userArr[i]->data());
    }
    delete[] userArr;
    return flag;
}
StatusType Group::updateOnRemove(MovieWatcher *toBeRemoved){
    StatusType flag;
    flag = remover(toBeRemoved);
    if(flag != StatusType::SUCCESS)
        return flag;
    const int* userViews = toBeRemoved->getAllViewsArr();
    for(int i = 0; i < NUM_OF_GENRE; i++) {
        m_groupWatchHistory[i] -= userViews[i];
    }
    m_isVip-=toBeRemoved->isVip();
    return flag;
}

StatusType Group::remove(MovieWatcher *toBeRemoved) {
    StatusType flag;
    flag = updateOnRemove(toBeRemoved);
    if(flag != StatusType::SUCCESS)
        return flag;
    flag = m_members.remove(toBeRemoved->getId());
    if(flag != StatusType::SUCCESS)
        return flag;
    m_size--;
    return StatusType::SUCCESS;
}