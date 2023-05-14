//
// Created by user on 07/05/2023.
// and shachar

#ifndef DATA_STRUCTURES_WET_1_GROUP_H
#define DATA_STRUCTURES_WET_1_GROUP_H
#include "wet1util.h"
#include "AVL_MAP.h"
#include "MovieWatcher.h"
#include "User.h"

class User;
class Group : public MovieWatcher{
public:
    Group(int groupId);
    virtual ~Group() override;
    Group(const Group& group) = default;
    Group& operator=(const Group& group) = default;

    StatusType insert(User& user);
    virtual void watchMovie(Movie& movie) override;
    virtual void updateGroupGenre(Genre genre);

    virtual Genre getFavoriteGenre() const;
    virtual int getViewsGenre(Genre genre) const override;
    StatusType deleteGroup();

protected:
    virtual StatusType remove(MovieWatcher* toBeRemoved) override;
private:
    AVLTree <User*,int> m_members;
};


#endif //DATA_STRUCTURES_WET_1_GROUP_H
