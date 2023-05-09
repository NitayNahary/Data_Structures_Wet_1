//
// Created by user on 07/05/2023.
//

#include "User.h"
#include "Group.h"

User::User(int userId, bool isVip) : m_userId(userId), m_isVip(isVip), m_group(nullptr), m_watchHistory(), m_groupWatchHistory(){
    for(int i = 0; i < G; i++){
        m_watchHistory[i] = 0;
        m_groupWatchHistory[i] = 0;
    }
}

int User::getUserId() const {
    return m_userId;
}

bool User::isVip() const {
    return m_isVip;
}

bool User::setGroup(Group* group){
    if(isInGroup()) return false;
    m_group = group;
    const int* groupViews = m_group->getViewsAll();
    for(int i = 0; i < (int)Genre::NONE; i++){
        m_groupWatchHistory[i] += groupViews[i];
    }
    return true;
}

void User::removeGroup(){
    const int* groupViews = m_group->getViewsAll();
    for(int i = 0; i <= (int)Genre::NONE; i++){
        m_watchHistory[i] = m_watchHistory[i] + groupViews[i] - m_groupWatchHistory[i];
        m_groupWatchHistory[i] = 0;
    }
    m_group = nullptr;
}

bool User::isInGroup() const {
    return (m_group != nullptr);
}

int User::getViews(Genre genre) const {
    int watchIndex = int(genre);
    if(!m_group)
        return m_watchHistory[watchIndex];
    const int* groupViews = m_group->getViewsAll();
    return m_watchHistory[watchIndex] + groupViews[watchIndex] - m_groupWatchHistory[watchIndex];
}
const int* User::getAllGenreViews() const {
    return m_watchHistory;
}

void User::watchMovie(Movie& movie){
    Genre movieGenre = movie.getMovieGenre();
    if(movieGenre == Genre::NONE)
        return;
    movie.addWatch(1);
    m_watchHistory[(int)movieGenre]++;
    m_watchHistory[(int)Genre::NONE]++;
    if(m_group)
        m_group->updateGWH(movieGenre);
}

