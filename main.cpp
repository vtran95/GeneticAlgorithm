#include <iostream>
#include "CityGenerator.hpp"
#include "Tour.hpp"
#include "Population.hpp"

#define CITIES_IN_TOUR 32
#define POPULATION_SIZE 32
#define MUTATION_RATE 0.30
#define IMPROVEMENT_FACTOR 1.2
#define ITERATIONS 1000

int main() {

    // Generator class that creates a number of cities
    CityGenerator gen;

    // Creates a master list of cities and assigns to a vector
    vector<City> masterList = gen.createList(CITIES_IN_TOUR);

    // Prints the cities just for testing
    for (auto it = masterList.begin(); it != masterList.end(); ++it) {
        cout << *it;
    }

    // Create a new population using the masterList of Cities and with
    // the set POPULATION_SIZE
    Population pop(masterList, POPULATION_SIZE);

    // Get the shortest distance
    double best_distance = pop.getBestFitnessRating();

    // Assign the initial best distance to be the base distance
    double base_distance = best_distance;

    // Initialize loop counter
    int loop = 0;

    while ((base_distance/best_distance < IMPROVEMENT_FACTOR) && (loop < ITERATIONS)) {
        // Move the elite tour to the front of the loop
        pop.moveEliteToFront();
        // Perform crossover algorithm
        pop.crossover();
        // Mutate cities in each Tour in the Population
        pop.mutate(MUTATION_RATE);
        // Check if the elite tour has changed
        bool isNewElite = pop.setEliteIter();
        string isNewEliteString = isNewElite ? "true" : "false";
        // Get the new best distance
        best_distance = pop.getBestFitnessRating();

        // Print report of each iteration
        cout << "Iteration: " << loop << endl;
        cout << "New Elite? " << isNewEliteString << endl;
        cout << "Best distance: " << best_distance << endl << endl;

        loop++;
    }

   double percent_improved = ((base_distance/best_distance) - 1) * 100;

    // Print final report
    cout << "===== Final Report =====" << endl;
    cout << "Total Iterations: " << loop << endl;
    cout << "Base distance " << base_distance << endl;
    cout << "Best distance: " << best_distance << endl;
    cout << "Improved by: " << percent_improved << "%" << endl;


//    cout << endl << pop;
//
//    cout << pop.getBestFitnessRating() << endl;
//    cout << "=======" << endl;
//
//    pop.crossover();
//    cout << "=======" << endl;
//    cout << pop << endl;
//    cout << "=======" << endl;
//    pop.mutate(MUTATION_RATE);
//    cout << pop << endl;

    return 0;
}
