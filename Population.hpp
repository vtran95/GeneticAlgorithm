//
// Created by Vincent on 2020-11-25.
//

#ifndef GENETICALGORITHM_POPULATION_HPP
#define GENETICALGORITHM_POPULATION_HPP

#include <iterator>
#include "Tour.hpp"

#define PARENT_POOL_SIZE 5
#define NUMBER_OF_PARENTS 2

class Population {
    vector<City> masterList;
    vector<Tour> tours;
    int max;
    vector<Tour>::iterator eliteIter;
    bool eliteIterFlag;

public:
    Population(vector<City> cities, int max);
    Population(vector<City> masterList, vector<Tour> tours);

    // Copy constructor
    Population(const Population &copy_pop);

    // Destructor
    ~Population();

    // Getter for returning all tours
    vector<Tour> getTours() const;

    // Setter for setting new tours
    void setTours(vector<Tour> t);

    // Return the tour at the index
    Tour getAt(int index) const;

    // Return the best tour
    Tour getBestTour() const;

    // Return the fitness rating of the elite tour
    double getBestFitnessRating() const;

    // Find the Tour with the best fitness, and set to eliteIter
    // Return true if a new iterator is set, else return false if it's the same
    bool setEliteIter();

    // moves the elite tour to the front of the list
    void moveEliteToFront();

    // Return a set of random tours used as a parent for crossover
    Population makeParent();

    // Perform crossover algorithm to generate new Tours
    void crossover();

    // Mutate each Tour by swapping cities at random
    // depending on the double rate given
    void mutate(double rate);

    // an overloaded assignment = operator for the copy-and-swap algorithm
    // PRE: other represents the tour that gets assigned
    Population &operator=(Population other);

    // a Tour swap operator
    friend void popSwap(Population &original, Population &other);

    // Overloaded insertion operator for printing to ostream
    friend ostream& operator<<(ostream& os, const Population& pop);
};

#endif //GENETICALGORITHM_POPULATION_HPP
