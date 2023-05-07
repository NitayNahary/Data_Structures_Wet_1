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

