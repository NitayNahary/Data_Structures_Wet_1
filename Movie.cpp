//
// Created by user on 07/05/2023.
//

#include "Movie.h"
Movie::Movie(int movieId, Genre genre, int initialViews, bool vipOnly) : m_movieId(movieId), m_genre(genre),
                                                                          m_views(initialViews), m_vipOnly(vipOnly){
    m_rating = 0;
    m_numOfReaters = 0;
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
    return (double)m_rating / (double)m_numOfReaters;
}

void Movie::addRating(int rating) {
    m_rating += rating;
    m_numOfReaters++;
}

void Movie::addWatch() {
    m_views++;
}

bool operator>(const Movie& movie1, const Movie& movie2){
    if(movie1.getRating() > movie2.getRating())
        return true;
    else if(movie1.getRating() < movie2.getRating())
        return false;
    else{
        if(movie1.getMovieViews() > movie2.getMovieViews())
            return true;
        else if(movie1.getMovieViews() < movie2.getMovieViews())
            return false;
        else{
            if(movie1.m_movieId > movie2.m_movieId)
                return true;
            return false;
        }
    }
}

bool operator==(const Movie& movie1, const Movie& movie2){
    return movie1.m_movieId == movie2.m_movieId;
}
