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

private:
    int m_movieId;
    Genre m_genre;
    int m_views;
    bool m_vipOnly;
    int m_rating;
};




#endif //DATA_STRUCTURES_WET_1_MOVIE_H
