//
// Created by Vincent on 2020-11-25.
//

#ifndef GENETICALGORITHM_POPULATION_HPP
#define GENETICALGORITHM_POPULATION_HPP

#include "Tour.hpp"

#define PARENT_POOL_SIZE 5

class Population {
    vector<City> masterList;
    vector<Tour> tours;
    int max;

    // moves the elite tour to the front of the list
    void moveEliteToFront();
public:
    Population(vector<City> cities, int max);
    Population(vector<City> masterList, vector<Tour> tours);

    // Copy constructor
    Population(const Population &copy_pop);

    // Destructor
    ~Population();

    // Getter for returning all tours
    vector<Tour> getTours() const;

    // Return the tour at the index
    Tour getAt(int index) const;

    // Return the best tour
    Tour getBestTour() const;

    // Move the tour with the best fitness rating to the front
    // of the vector and return it's fitness rating
    double getBestFitnessRating() const;

    // Return a set of random tours used as a parent for crossover
    Population makeParent();

    // Perform crossover
    void crossover();

    // an overloaded assignment = operator for the copy-and-swap algorithm
    // PRE: other represents the tour that gets assigned
    Population &operator=(Population other);

    // a Tour swap operator
    friend void popSwap(Population &original, Population &other);

    // Overloaded insertion operator for printing to ostream
    friend ostream& operator<<(ostream& os, const Population& pop);
};

#endif //GENETICALGORITHM_POPULATION_HPP
