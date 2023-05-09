//
// Created by user on 07/05/2023.
//

#include "Group.h"

Group::Group(int groupId) : m_GroupId(groupId) {
    m_members = AVLTree<User, int>();
    m_groupGenreHist = new int[5]();
}

int Group::getGroupId() const {
    return m_GroupId;
}

bool Group::isempty() const{
    return m_members.empty();
}


StatusType Group::insert(User& user){
    if(!user.setGroup(this))
        return StatusType::FAILURE;
    StatusType result = m_members.insert(&user, user.getUserId());
    if(result != StatusType::SUCCESS)
        return result;
    m_groupWatchHistory[COMEDY] += user.getComedy();
    m_groupWatchHistory[ACTION] += user.getAction();
    m_groupWatchHistory[DRAMA] += user.getDrama();
    m_groupWatchHistory[FANTASY] += user.getFantasy();
    return StatusType::SUCCESS;
}

bool Group::isVip() const{
    return m_isVip;
}

Genre Group::getFavoriteGenre() const{
    int view_count = m_groupWatchHistory[COMEDY];
    Genre result = Genre::COMEDY;
    if(view_count < m_groupWatchHistory[DRAMA]){
        view_count = m_groupWatchHistory[DRAMA];
        result = Genre::DRAMA;
    }
    if(view_count < m_groupWatchHistory[ACTION]){
        view_count = m_groupWatchHistory[ACTION];
        result = Genre::ACTION;
    }
    if(view_count < m_groupWatchHistory[FANTASY]){
        view_count = m_groupWatchHistory[FANTASY];
        result = Genre::FANTASY;
    }
    return result;
}

void Group::updateGWH(Genre genre){
    switch (genre) {
        case: Genre::COMEDY:
            m_groupWatchHistory[COMEDY]++;
            break;
        case: Genre::ACTION:
            m_groupWatchHistory[ACTION]++;
            break;
        case: Genre::DRAMA:
            m_groupWatchHistory[DRAMA]++;
            break;
        case: Genre::FANTASY:
            m_groupWatchHistory[FANTASY]++;
            break;
        default:
            return;
    }
}


