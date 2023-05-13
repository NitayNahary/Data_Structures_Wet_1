//
// Created by shach on 5/9/2023.
//

#ifndef DATA_STRUCTURES_WET_1_MOVIEWATCHER_H
#define DATA_STRUCTURES_WET_1_MOVIEWATCHER_H

#include "wet1util.h"
#include "Movie.h"
#define NUM_OF_GENRE 5

class MovieWatcher{
public:
    MovieWatcher(int userId);
    virtual ~MovieWatcher() = default;
    MovieWatcher(const MovieWatcher& movieWatcher) = default;
    MovieWatcher& operator=(const MovieWatcher& movieWatcher) = default;

    virtual void watchMovie(Movie& movie);

    virtual int getId() const;
    bool isEmpty() const;
    virtual bool isVip() const;
    virtual const int * getAllViewsArr() const;
    virtual int getViewsGenre(Genre genre) const = 0;

protected:
    StatusType remover(MovieWatcher* removeFrom, MovieWatcher* removeMe = nullptr);
    virtual StatusType remove(MovieWatcher* toBeRemoved) = 0;

    int m_Id;
    bool m_isVip;
    int m_watchHistory[NUM_OF_GENRE];
    int m_groupWatchHistory[NUM_OF_GENRE];
    int m_size;
};



#endif //DATA_STRUCTURES_WET_1_MOVIEWATCHER_H
