//
// Created by Vincent on 2020-11-24.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include "City.hpp"

class Tour {
    vector<City*> cityPointers;
    double fitnessRating;

    // Calculate distance between two cities
    double calcDistance(City c1, City c2);

    // Calculate fitness rating of Tour object
    double calcFitnessRating();
public:
    // Constructor taking in the master list of cities as reference
    Tour(vector<City> &masterList);

    // Destructor
    ~Tour();

    // Getter for the City pointers vector
    vector<City*> getCityPointers() const;

    // Getter for the fitness rating
    double getFitnessRating() const;

    // Overloaded insertion operator for printing to ostream
    friend ostream& operator<<(ostream& os, const Tour& tour);
};

#endif //GENETICALGORITHM_TOUR_HPP
