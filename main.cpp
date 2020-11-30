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

    // Prints the master list of cities just for testing
//    for (auto it = masterList.begin(); it != masterList.end(); ++it) {
//        cout << *it;
//    }

    // Create a new population using the masterList of Cities and with
    // the set POPULATION_SIZE
    Population pop(masterList, POPULATION_SIZE);
    // Get the shortest distance
    double best_distance = pop.getBestFitnessRating();
    // Assign the initial best distance to be the base distance
    double base_distance = best_distance;
    // Base route
    Tour baseTour = pop.getBestTour();
    vector<City*> baseCities = baseTour.getCityPointers();
    // Initialize loop counter
    int loop = 0;
    // Initialize percent improved
    double percent_improved = 0;

    // Print the base distance before the genetic algorithm starts
    cout << endl << "Base distance " << base_distance << endl << endl;

    while ((base_distance/best_distance < IMPROVEMENT_FACTOR) && (loop < ITERATIONS)) {
        // Move the elite tour to the front of the loop
        pop.moveEliteToFront();
        // Perform crossover algorithm
        pop.crossover();
        // Mutate cities in each Tour in the Population
        pop.mutate(MUTATION_RATE);
        // Check if the elite tour has changed
        bool isNewElite = pop.setEliteIter();
        string isNewEliteString = isNewElite ? "Yes" : "No";
        // Get the new best distance
        best_distance = pop.getBestFitnessRating();
        // Calculate how much the best distance improved from the base distance
        percent_improved = ((base_distance/best_distance) - 1) * 100;

        // Print report of each iteration
        cout << "Iteration: " << loop << endl;
        cout << "Best distance: " << best_distance << endl;
        cout << "New elite found? " << isNewEliteString << endl;
        cout << "Improved by: " << percent_improved << "%" << endl << endl;

        loop++;
    }

    // Calculate how much the best distance improved from the base distance
    bool betterThanFactor = (base_distance/best_distance) > IMPROVEMENT_FACTOR;
    string improvedString = betterThanFactor ? "Yes" : "No";

    // Get the final best tour
    Tour bestTour = pop.getBestTour();
    vector<City*> bestCities = bestTour.getCityPointers();

    // Print final report
    cout << endl;
    cout << "===== Final Report =====" << endl;
    cout << "Total Iterations: " << loop << endl;
    cout << "Base distance " << base_distance << endl;
    cout << "Best distance: " << best_distance << endl;
    cout << "Improvement factor achieved? " << improvedString << endl;
    cout << "Improved by: " << percent_improved << "%" << endl;

    // Print the ID for each city in the base tour
    cout << "Base Tour: " << endl;
    for (auto it = baseCities.begin(); it != baseCities.end()-1; ++it) {
        cout << (**it).getId() << ", ";
    }
    cout << (**(baseCities.end()-1)).getId() << endl;

    // Print the ID for each city in the best tour
    cout << "Best Tour: " << endl;
    for (auto it = bestCities.begin(); it != bestCities.end()-1; ++it) {
        cout << (**it).getId() << ", ";
    }
    cout << (**(bestCities.end()-1)).getId() << endl;

    return 0;
}
