//
// Created by user on 07/05/2023.
//

#ifndef DATA_STRUCTURES_WET_1_USER_H
#define DATA_STRUCTURES_WET_1_USER_H
#define G 5
#include "wet1util.h"
#include "Movie.h"
#include "Group.h"

class User{

public:
    User(int userId, bool isVip);
    ~User() = default;
    User(const User& user) = default;
    User& operator=(const User& user) = default;

    void watchMovie(Movie& movie);
    bool setGroup(Group* group);

    int getUserId() const;
    bool isVip() const;
    bool isInGroup() const;
    const int * getAllViewsArr() const;
    int getViewsGenre(Genre genre) const;

private:
    int m_userId;
    bool m_isVip;
    Group* m_group;
    int m_watchHistory[G];
    int m_groupWatchHistory[G];
    void removeGroup() friend Group;
};



#endif //DATA_STRUCTURES_WET_1_USER_H
