//
// Created by user on 07/05/2023.
//

#include "User.h"

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
    if(isInGroup) return false;
    m_group = group;
    m_groupWatchHistory[COMEDY] = group.getComedy();
    m_groupWatchHistory[ACTION] = group.getAction();
    m_groupWatchHistory[DRAMA] = group.getDrama();
    m_groupWatchHistory[FANTASY] = group.getFantasy();
    m_groupWatchHistory[NONE] = group.getAll();
    return;
}

void User::removeGroup(){
    m_watchHistory[COMEDY] = getNumOfViews(Genre::COMEDY);
    m_watchHistory[DRAMA] = getNumOfViews(Genre::DRAMA);
    m_watchHistory[ACTION] = getNumOfViews(Genre::ACTION);
    m_watchHistory[FANTASY] = getNumOfViews(Genre::FANTASY);
    m_watchHistory[NONE] = getNumOfViews(Genre::NONE);
    for(int i = 0; i < G; i++){
        m_groupWatchHistory[i] = 0;
    }
    m_group = nullptr;
}

bool User::isInGroup() const {
    return m_group ? true : false;
}

int User::getNumOfViews(Genre genre) const {
    int watchSum = 0;
    switch (genre) {
        case: Genre::COMEDY:
            watchSum += m_watchHistory[COMEDY];
            if(m_group){
                watchSum += m_group->getComedy() - m_groupWatchHistory[COMEDY];
            }
            break;
        case: Genre::ACTION:
            watchSum += m_watchHistory[ACTION];
            if(m_group){
                watchSum += m_group->getAction() - m_groupWatchHistory[ACTION];
            }
            break;
        case: Genre::DRAMA:
            watchSum += m_watchHistory[DRAMA];
            if(m_group){
                watchSum += m_group->getDrama() - m_groupWatchHistory[DRAMA];
            }
            break;
        case: Genre::FANTASY:
            watchSum += m_watchHistory[FANTASY];
            if(m_group){
                watchSum += m_group->getFantasy() - m_groupWatchHistory[FANTASY];
            }
            break;
        default:
            watchSum += m_watchHistory[NONE];
            if(m_group){
                watchSum += m_group->getAll() - m_groupWatchHistory[NONE];
            }
            break;
    }
    return watchSum;
}

void User::watchMovie(Movie& movie){
    movie.addWatch();
    switch (movie.getMovieGenre()) {
        case: Genre::COMEDY:
            m_watchHistory[COMEDY]++;
            break;
        case: Genre::ACTION:
            m_watchHistory[ACTION]++;
            break;
        case: Genre::DRAMA:
            m_watchHistory[DRAMA]++;
            break;
        case: Genre::FANTASY:
            m_watchHistory[FANTASY]++;
            break;
        default:
            return;
    }
    m_watchHistory[NONE]++;
    if(m_group)
        m_group.updateGWH(movie.getMovieGenre());
}
