//
// Created by user on 07/05/2023.
//

#ifndef DATA_STRUCTURES_WET_1_GROUP_H
#define DATA_STRUCTURES_WET_1_GROUP_H
#include "wet1util.h"
#include "AVL_MAP.h"
#include "User.h"
class Group{

public:
    Group(int groupId);
    ~Group() = default;
    Group(const Group& group) = default;
    Group& operator=(const Group& group) = default;

    int getGroupId() const;



private:
    int m_GroupId;
    AVLTree <User,int> m_members;
    int* m_groupGenreHist;
    Genre m_favoriteGenre;

};


#endif //DATA_STRUCTURES_WET_1_GROUP_H
