//
// Created by user on 07/05/2023.
// and shachar

#ifndef DATA_STRUCTURES_WET_1_GROUP_H
#define DATA_STRUCTURES_WET_1_GROUP_H
#include "wet1util.h"
#include "AVL_MAP.h"
#include "User.h"
#define G 5
class Group{

public:
    Group(int groupId);
    ~Group() = default;
    Group(const Group& group) = default;
    Group& operator=(const Group& group) = default;

    StatusType insert(User& user);
    void watchMovie(Movie& movie);
    int getGroupId() const;
    void updateGWH(Genre genre);

    bool isEmpty() const;
    bool isVip() const;
    int getAction() const;
    int getFantasy() const;
    int getDrama() const;
    int getComedy() const;
    int getAll() const;
    Genre getFavoriteGenre() const;

private:
    int m_GroupId;
    AVLTree <User*,int> m_members;
    int[G] m_watchHistory;
    int[G] m_groupWatchHistory;
    bool m_isVip;
};


#endif //DATA_STRUCTURES_WET_1_GROUP_H
