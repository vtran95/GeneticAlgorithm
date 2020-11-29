#include <iostream>
#include "CityGenerator.hpp"
#include "Tour.hpp"
#include "Population.hpp"

#define CITIES_IN_TOUR 10
#define POPULATION_SIZE 10

int main() {
    // Generator class that creates a number of cities
    CityGenerator gen;

    // Creates a master list of cities and assigns to a vector
    vector<City> masterList = gen.createList(CITIES_IN_TOUR);

    // Prints the cities just for testing
    for (auto it = masterList.begin(); it != masterList.end(); ++it) {
        cout << *it;
    }

    // Creates a tour from the cities in masterList
//    Tour tour1(masterList);

    // Print the contents of the tour
//    cout << endl << tour1;

    Population pop(masterList, POPULATION_SIZE);
    cout << endl << pop;

    cout << pop.getBestFitnessRating() << endl;
    cout << "=======" << endl;

    pop.crossover();

    return 0;
}
