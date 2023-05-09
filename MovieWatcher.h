//
// Created by shach on 5/9/2023.
//

#ifndef DATA_STRUCTURES_WET_1_MOVIEWATCHER_H
#define DATA_STRUCTURES_WET_1_MOVIEWATCHER_H

#include "wet1util.h"
#include "Movie.h"
#include "Group.h"

class MovieWatcher{
public:
    MovieWatcher(int userId);
    virtual ~MovieWatcher();
    MovieWatcher(const MovieWatcher& movieWatcher) = default;
    MovieWatcher& operator=(const MovieWatcher& movieWatcher) = default;

    virtual void watchMovie(Movie& movie);

    virtual int getId() const;
    virtual bool isVip() const = 0;
    virtual const int * getAllViewsArr() const = 0;
    virtual int getViewsGenre(Genre genre) const = 0;
protected:
    virtual void remove() = 0;
private:
    int m_Id;
    bool m_isVip;
    int m_watchHistory[G];
    int m_groupWatchHistory[G];
    int size;
};



#endif //DATA_STRUCTURES_WET_1_MOVIEWATCHER_H
