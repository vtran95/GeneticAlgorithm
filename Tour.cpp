//
// Created by Vincent on 2020-11-24.
//

#include "Tour.hpp"

// Constructor creates a vector of city pointers from the masterList
// and randomly shuffles the pointers. Also determines the fitness
// rating of the Tour object.
Tour::Tour(vector<City> &masterList) {
    for (auto it = masterList.begin(); it != masterList.end(); ++it) {
        City* ptr = &(*it);
        cityPointers.push_back(ptr);
    }

    random_device rd;
    auto rnd = default_random_engine { rd() };

    shuffle(cityPointers.begin(), cityPointers.end(), rnd);
    fitnessRating = calcFitnessRating();
}

// Destructor to free pointers and clear the vector
Tour::~Tour() {
    cityPointers.clear();
}

// Returns the cityPointers vector
vector<City*> Tour::getCityPointers() const {
    return cityPointers;
}

// Returns the fitness rating
double Tour::getFitnessRating() const {
    return fitnessRating;
}

// Calculates the distance between two cities
double Tour::calcDistance(City c1, City c2) {
    double xDist = c2.getX() - c1.getX();
    double yDist = c2.getY() - c1.getY();
    return sqrt(pow(xDist,2) + pow(yDist, 2));
}

// TO DO: Currently just returns the total distance.
// Needs to convert the total distance into a fitness rating.
double Tour::calcFitnessRating() {
    double totalDist = 0;
    for (auto it = cityPointers.begin(); it != cityPointers.end() - 1; ++it) {
        City c1 = **it;
        City c2 = **it;
        totalDist += calcDistance(c1, c2);
    }
    totalDist += calcDistance(**(cityPointers.end()-1), **cityPointers.begin());

    return totalDist;
}

// Overloaded insertion operator prints list of City objects pointed to in Tour
ostream &operator<<(ostream &os, const Tour& tour) {
    for (auto ptr : tour.getCityPointers()) {
        os << *ptr;
    }
    os << "Fitness rating: " << tour.getFitnessRating() << endl;
    return os;
}