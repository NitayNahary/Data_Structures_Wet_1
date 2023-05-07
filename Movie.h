//
// Created by user on 07/05/2023.
//
#include "wet1util.h"
#ifndef DATA_STRUCTURES_WET_1_MOVIE_H
#define DATA_STRUCTURES_WET_1_MOVIE_H

class Movie{

public:
    Movie(int movieId, Genre genre, int initialViews, bool vipOnly);
    ~Movie() = default;
    Movie(const Movie& movie) = default;
    Movie& operator=(const Movie& movie) = default;

    int getMovieId() const;
    Genre getMovieGenre() const;
    int getMovieViews() const;
    bool isVipOnly() const;
    double getRating() const;
    void addRating(int rating);
    void addWatch();
    friend bool operator>(const Movie& movie1, const Movie& movie2);
    friend bool operator==(const Movie& movie1, const Movie& movie2);

        private:
    int m_movieId;
    Genre m_genre;
    int m_views;
    bool m_vipOnly;
    int m_rating;
    int m_numOfReaters;
};

bool operator>=(const Movie& movie1, const Movie& movie2){
    return ((movie1 > movie2) || (movie1 == movie2));
}
bool operator<(const Movie& movie1, const Movie& movie2){
    return (!(movie1>=movie2));
}
bool operator<=(const Movie& movie1, const Movie& movie2){
    return ((movie1 < movie2) || (movie1 == movie2));
}
bool operator!=(const Movie& movie1, const Movie& movie2){
    return !(movie1 == movie2);
}

#endif //DATA_STRUCTURES_WET_1_MOVIE_H
