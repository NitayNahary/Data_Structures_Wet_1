//
// Created by user on 07/05/2023.
//

#include "Group.h"

Group::Group(int groupId) : m_GroupId(groupId),m_members(), m_watchHistory(), m_groupWatchHistory() , m_isVip(false){
    for(int i = 0; i < G; i++){
        m_watchHistory[i] = 0;
        m_groupWatchHistory[i] = 0;
    }
}

int Group::getGroupId() const {
    return m_GroupId;
}

bool Group::isEmpty() const{
    return m_members.empty();
}


StatusType Group::insert(User& user){
    if(!user.setGroup(this))
        return StatusType::FAILURE;
    StatusType result = m_members.insert(&user, user.getUserId());
    if(result != StatusType::SUCCESS)
        return result;
    const int* userViews = user.getAllViewsArr();
    for(int i = 0; i < (int)Genre::NONE; i++){
        m_groupWatchHistory[i] += userViews[i];
    }
    return StatusType::SUCCESS;
}

bool Group::isVip() const{
    return m_isVip;
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

}

const int *Group::getAllViewsArr() const {
    return m_watchHistory;
}

int Group::getViewsGenre(Genre genre) const {
    return m_watchHistory[(int)genre];
}


