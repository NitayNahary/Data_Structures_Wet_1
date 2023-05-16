//
// Created by user on 07/05/2023.
//

#ifndef DATA_STRUCTURES_WET_1_USER_H
#define DATA_STRUCTURES_WET_1_USER_H
#include "wet1util.h"
#include "MovieWatcher.h"
#include "Group.h"
class Group;
class User : public MovieWatcher{
public:
    User(int userId, bool isVip);
    ~User() override = default;
    User(const User& user) = default;
    User& operator=(const User& user) = default;
    StatusType destroy() override;
    virtual void watchMovie(Movie& movie) override;

    bool setGroup(Group* group);
    bool isInGroup() const;
    int getViewsGenre(Genre genre) const override;
protected:
    virtual StatusType remove(MovieWatcher* toBeRemoved) override;
private:
    Group* m_group;
};



#endif //DATA_STRUCTURES_WET_1_USER_H
