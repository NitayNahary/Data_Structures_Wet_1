//
// Created by user on 07/05/2023.
//

#include "Movie.h"
Movie::Movie(int movieId, Genre genre, int initialViews, bool vipOnly) : m_movieId(movieId), m_genre(genre),
                                                                          m_views(initialViews), m_vipOnly(vipOnly){
    m_rating = 0;
}

int Movie::getMovieId() const {
    return m_movieId;
}

Genre Movie::getMovieGenre() const {
    return m_genre;
}

int Movie::getMovieViews() const {
    return m_views;
}

bool Movie::isVipOnly() const {
    return m_vipOnly;
}

double Movie::getRating() const {
    return m_rating/m_views;
}

