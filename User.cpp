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
    m_groupWatchHistory[(int)Genre::COMEDY] = group->getComedy();
    m_groupWatchHistory[(int)Genre::ACTION] = group->getAction();
    m_groupWatchHistory[(int)Genre::DRAMA] = group->getDrama();
    m_groupWatchHistory[(int)Genre::FANTASY] = group->getFantasy();
    m_groupWatchHistory[(int)Genre::NONE] = group->getAll();
    return true;
}

void User::removeGroup(){
    m_watchHistory[(int)Genre::COMEDY] = getNumOfViews(Genre::COMEDY);
    m_watchHistory[(int)Genre::DRAMA] = getNumOfViews(Genre::DRAMA);
    m_watchHistory[(int)Genre::ACTION] = getNumOfViews(Genre::ACTION);
    m_watchHistory[(int)Genre::FANTASY] = getNumOfViews(Genre::FANTASY);
    m_watchHistory[(int)Genre::NONE] = getNumOfViews(Genre::NONE);
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
        case Genre::COMEDY:
            watchSum += m_watchHistory[(int)Genre::COMEDY];
            if(m_group){
                watchSum += m_group->getComedy() - m_groupWatchHistory[(int)Genre::COMEDY];
            }
            break;
        case Genre::ACTION:
            watchSum += m_watchHistory[(int)Genre::ACTION];
            if(m_group){
                watchSum += m_group->getAction() - m_groupWatchHistory[(int)Genre::ACTION];
            }
            break;
        case Genre::DRAMA:
            watchSum += m_watchHistory[(int)Genre::DRAMA];
            if(m_group){
                watchSum += m_group->getDrama() - m_groupWatchHistory[(int)Genre::DRAMA];
            }
            break;
        case Genre::FANTASY:
            watchSum += m_watchHistory[(int)Genre::FANTASY];
            if(m_group){
                watchSum += m_group->getFantasy() - m_groupWatchHistory[(int)Genre::FANTASY];
            }
            break;
        default:
            watchSum += m_watchHistory[(int)Genre::NONE];
            if(m_group){
                watchSum += m_group->getAll() - m_groupWatchHistory[(int)Genre::NONE];
            }
            break;
    }
    return watchSum;
}

void User::watchMovie(Movie& movie){
    movie.addWatch();
    switch (movie.getMovieGenre()) {
        case Genre::COMEDY:
            m_watchHistory[(int)Genre::COMEDY]++;
            break;
        case Genre::ACTION:
            m_watchHistory[(int)Genre::ACTION]++;
            break;
        case Genre::DRAMA:
            m_watchHistory[(int)Genre::DRAMA]++;
            break;
        case Genre::FANTASY:
            m_watchHistory[(int)Genre::FANTASY]++;
            break;
        default:
            return;
    }
    m_watchHistory[(int)Genre::NONE]++;
    if(m_group)
        m_group->updateGWH(movie.getMovieGenre());
}
