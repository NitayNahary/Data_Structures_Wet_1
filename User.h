//
// Created by user on 07/05/2023.
//

#ifndef DATA_STRUCTURES_WET_1_USER_H
#define DATA_STRUCTURES_WET_1_USER_H

#include "wet1util.h"
#include "Movie.h"

class User{

public:
    User(int userId, bool isVip);
    ~User() = default;
    User(const User& user) = default;
    User& operator=(const User& user) = default;

    void watchMovie(Movie& movie);

    int getUserId() const;
    bool isVip() const;
    bool isInGroup() const;
    int getNumOfViews(Genre genre) const;


private:
    int m_userId;
    bool m_isVip;
    bool m_isInGroup;
    int m_numOfViews;
    int* m_genreHist;
};



#endif //DATA_STRUCTURES_WET_1_USER_H
