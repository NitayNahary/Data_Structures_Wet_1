//
// Created by user on 07/05/2023.
//

#include "User.h"

User::User(int userId, bool isVip, bool isInGroup) : m_userId(userId), m_isVip(isVip){
    m_isInGroup = false;
    m_numOfViews = 0;
    m_genreHist = new int[5]();
}

int User::getUserId() const {
    return m_userId;
}

bool User::isVip() const {
    return m_isVip;
}

bool User::isInGroup() const {
    return m_isInGroup;
}

int User::getNumOfViews() const {
    return m_numOfViews;
}
