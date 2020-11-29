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

Tour::Tour(vector<City *> cities) : cityPointers(cities) {
    fitnessRating = calcFitnessRating();
}

// copy constructor
Tour::Tour(const Tour &copy_tour) :
cityPointers(copy_tour.getCityPointers()), fitnessRating(copy_tour.getFitnessRating()) {}

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

// Return size of tour which is the size of the cityPointers vector
int Tour::size() const {
    return cityPointers.size();
}

// Return a copy of the Tour from begin index to end index
Tour Tour::copy(int begin, int end) {
    auto beginIt = cityPointers.begin() + begin;
    auto endIt = cityPointers.begin() + end;

    vector<City *> subCities(beginIt, endIt);
    Tour subTour(subCities);
    return subTour;
}

// Concat the reference tour to this tour (ignoring duplicates)
Tour &Tour::concat(const Tour &tour) {
    vector<City*> addCities = tour.getCityPointers();

    for (int i = 0; i < addCities.size(); i++) {
        // checks to see if the City* pointer already exists in this Tour
        if (!isDuplicate(addCities[i])) {
            this->cityPointers.push_back(addCities.at(i));
        }
    }
    return *this;
}

// Check to see if the City* pointer exists in this Tour's cityPointers
bool Tour::isDuplicate(City *key) {
    // Searches for the City* pointer and returns false if the iterator reaches the end, else true
    if (find(cityPointers.begin(), cityPointers.end(), key) == cityPointers.end()) {
        return false;
    } else {
        return true;
    }
}

// Calculates the distance between two cities
double Tour::calcDistance(City c1, City c2) {
    double xDist = c2.getX() - c1.getX();
    double yDist = c2.getY() - c1.getY();
    return sqrt(pow(xDist,2) + pow(yDist, 2));
}

// Returns the total distance
double Tour::calcFitnessRating() {
    double totalDist = 0;
    for (auto it = cityPointers.begin(); it != prev(cityPointers.end()); ++it) {
        auto it2 = next(it);
        City c1 = **it;
        City c2 = **it2;
        totalDist += calcDistance(c1, c2);
    }
    totalDist += calcDistance(**(cityPointers.end()-1), **cityPointers.begin());

    return totalDist;
}

// overloaded assignment operator=
Tour &Tour::operator=(Tour other) {
    tourSwap(*this, other);
    return *this;
}

// friend function swap
void tourSwap(Tour &original, Tour &other) {
    swap(original.cityPointers, other.cityPointers);
    swap(original.fitnessRating, other.fitnessRating);
}

// Overloaded insertion operator prints list of City objects pointed to in Tour
ostream &operator<<(ostream &os, const Tour& tour) {
    for (auto ptr : tour.getCityPointers()) {
        os << *ptr;
    }
    os << "Fitness rating: " << tour.getFitnessRating() << endl;
    return os;
}