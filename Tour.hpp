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
    // The vector of city pointers in order of the route
    vector<City*> cityPointers;
    // This tours total distance
    double fitnessRating;

    // Calculate distance between two cities
    double calcDistance(City c1, City c2);

    // Calculate fitness rating of Tour object
    double calcFitnessRating();
public:
    // Constructor taking in the master list of cities as reference
    Tour(vector<City> &masterList);

    // Constructor taking in a vector of City pointers
    Tour(vector<City*> cities);

    // Copy constructor
    Tour(const Tour &copy_tour);

    // Destructor
    ~Tour();

    // Getter for the City pointers vector
    vector<City*> getCityPointers() const;

    // Getter for the fitness rating
    double getFitnessRating() const;

    // Return size of tour which is the size of the cityPointers vector
    int size() const;

    // Return a copy of the Tour from begin index to end index
    Tour copy(int begin, int end);

    // Concat the reference tour to this tour (ignoring duplicates)
    Tour &concat(const Tour &tour);

    // Check to see if the City* pointer exists in this Tour's cityPointers
    bool isDuplicate(City* city);

    // Mutate this Tour by swapping Cities according to rate
    Tour &mutateCities(double rate);

    // an overloaded assignment = operator for the copy-and-swap algorithm
    // PRE: other represents the tour that gets assigned
    Tour &operator=(Tour other);

    // a Tour swap operator
    friend void tourSwap(Tour &original, Tour &other);

    // Overloaded insertion operator for printing to ostream
    friend ostream& operator<<(ostream& os, const Tour& tour);
};

#endif //GENETICALGORITHM_TOUR_HPP
