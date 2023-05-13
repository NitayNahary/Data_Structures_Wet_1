//
// Created by user on 07/05/2023.
//

#include "User.h"

User::User(int userId, bool isVip) : MovieWatcher(userId), m_group(nullptr){
    m_isVip = isVip;
    m_size = 1;
}

bool User::setGroup(Group* group){
    if(isInGroup()) return false;
    m_group = group;
    const int* groupViews = m_group->getAllViewsArr();
    for(int i = 0; i < NUM_OF_GENRE; i++){
        m_groupWatchHistory[i] += groupViews[i];
    }
    return true;
}

bool User::isInGroup() const {
    return (m_group != nullptr);
}

int User::getViewsGenre(Genre genre) const {
    int watchIndex = int(genre);
    if(!m_group)
        return m_watchHistory[watchIndex];
    int groupViews = m_group->getViewsGenre(genre);
    return m_watchHistory[watchIndex] + groupViews - m_groupWatchHistory[watchIndex];
}
const int * User::getAndUpdateAllViews(){
    if(!m_group)
        return m_watchHistory;
    const int * groupViews = m_group->getAllViewsArr();
    for(int i = 0; i < NUM_OF_GENRE; i++){
        m_watchHistory[i] = m_watchHistory[i] + groupViews[i] - m_groupWatchHistory[i];
        m_groupWatchHistory[i] = groupViews[i];
    }
    return m_watchHistory;
}


void User::watchMovie(Movie& movie){
    MovieWatcher::watchMovie(movie);
    if(m_group)
        m_group->updateGroup(movie.getMovieGenre());
}

User::~User() {
    remover(m_group, this);
}

StatusType User::remove(MovieWatcher* toBeRemoved){
    for(int & i : m_groupWatchHistory){
        i = 0;
    }
    m_group = nullptr;
    return StatusType::SUCCESS;
}