//
// Created by user on 07/05/2023.
//

#ifndef DATA_STRUCTURES_WET_1_USER_H
#define DATA_STRUCTURES_WET_1_USER_H

class User{

public:
    User(int userId, bool isVip, bool isInGroup);
    ~User() = default;
    User(const User& user) = default;
    User& operator=(const User& user) = default;

    int getUserId() const;
    bool isVip() const;
    bool isInGroup() const;
    int getNumOfViews() const;


private:
    int m_userId;
    bool m_isVip;
    bool m_isInGroup;
    int m_numOfViews;
    int* m_genreHist;
};



#endif //DATA_STRUCTURES_WET_1_USER_H
