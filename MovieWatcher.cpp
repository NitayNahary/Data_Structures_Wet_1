//
// Created by shach on 5/9/2023.
//

#include "MovieWatcher.h"

MovieWatcher::MovieWatcher(int userId) : m_Id(userId), m_isVip(false), m_watchHistory(), m_groupWatchHistory(), m_size(0){
    for(int i = 0; i < NUM_OF_GENRE; i++){
        m_watchHistory[i] = 0;
        m_groupWatchHistory[i] = 0;
    }
}

const int* MovieWatcher::getAllViewsArr() const {
    return m_watchHistory;
}

int MovieWatcher::getId() const {
    return m_Id;
}

bool MovieWatcher::isEmpty() const{
    return (m_size == 0);
}

bool MovieWatcher::isVip() const{
    return m_isVip;
}

void MovieWatcher::watchMovie(Movie &movie) {
    Genre movieGenre = movie.getMovieGenre();
    if(movieGenre == Genre::NONE)
        return;
    movie.addWatch(m_size);
    m_watchHistory[(int)movieGenre]++;
    m_watchHistory[(int)Genre::NONE]++;
}

StatusType MovieWatcher::remover(MovieWatcher *removeFrom, MovieWatcher *removeMe) {
    return removeFrom->remove(removeMe);
}




