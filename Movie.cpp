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
    return m_numOfReaters == 0 ? 0 : (double)m_rating / (double)m_numOfReaters;
}

void Movie::addRating(int rating) {
    m_rating += rating;
    m_numOfReaters++;
}

void Movie::addWatch(int numOfWatch) {
    m_views += numOfWatch;
}

bool operator>(const Movie& movie1, const Movie& movie2){
    if(movie1.getRating() < movie2.getRating())
        return true;
    else if(movie1.getRating() == movie2.getRating()) {
        if (movie1.getMovieViews() < movie2.getMovieViews())
            return true;
        else if (movie1.getMovieViews() == movie2.getMovieViews()){
            if (movie1.m_movieId > movie2.m_movieId)
                return true;
        }
    }
    return false;
}


bool operator==(const Movie& movie1, const Movie& movie2){
    return ((movie1.m_movieId == movie2.m_movieId) && (movie1.m_genre == movie2.m_genre) && (movie1.m_vipOnly == movie2.m_vipOnly)
            && (movie1.m_views == movie2.m_views) && (movie1.m_rating == movie2.m_rating) && (movie1.m_numOfReaters == movie2.m_numOfReaters));
}

bool Movie::operator>=(const Movie& movie2) const{
    return ((*this > movie2) || (*this == movie2));
}
bool Movie::operator<(const Movie& movie2) const{
    return (!(*this>=movie2));
}
bool Movie::operator<=(const Movie& movie2) const{
    return ((*this < movie2) || (*this == movie2));
}
bool Movie::operator!=(const Movie& movie2) const{
    return !(*this == movie2);
}