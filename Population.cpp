//
// Created by Vincent on 2020-11-25.
//

#include "Population.hpp"

// Constructor that creates a vector of Tour objects with size max
Population::Population(vector<City> cities, int max) : masterList(cities), max(max) {
    for (int i = 0; i < max; i++) {
        Tour t(masterList);
        tours.push_back(t);
    }
    moveEliteToFront();
}

// Constructor with masterList, and an already constructed vector of Tour objects
Population::Population(vector<City> masterList, vector<Tour> t) {
    this->masterList = masterList;
    this->tours = t;
    this->max = t.size();
    moveEliteToFront();
}

// Copy constructor
Population::Population(const Population &copy_pop) {
    masterList = copy_pop.masterList;
    tours = copy_pop.getTours();
    max = copy_pop.getTours().size();
    moveEliteToFront();
}

// Destructor
Population::~Population() {
    tours.clear();
}

// Finds the elite tour and swaps with the tour in the first index
void Population::moveEliteToFront() {
    // Immediately return if tours is empty
    if (tours.empty()) {
        return;
    }

    // Initialize the best fitness rating, and the iterator pointing at the tour with best fitness
    int bestFitness = tours[0].getFitnessRating();
    auto bestIter = tours.begin();

    // Loop through each tour to find the tour with the best fitness rating
    for (auto it = tours.begin(); it != tours.end(); ++it) {
        if ((*it).getFitnessRating() < bestFitness) {
            bestFitness = (*it).getFitnessRating();
            bestIter = it;
        }
    }

    // swap the first tour with the tour with best fitness
    iter_swap(tours.begin(), bestIter);
}

// Return all Tours
vector<Tour> Population::getTours() const {
    return tours;
}

// Set new tours for this Population
void Population::setTours(vector<Tour> t) {
    tours = t;
    moveEliteToFront();
}

Tour Population::getAt(int index) const {
    return tours[index];
}

// Returns the best tour
Tour Population::getBestTour() const {
    return tours[0];
}

// Returns the best fitness rating
double Population::getBestFitnessRating() const {
    // Return -1 if tours is empty, else return the tour in the front
    // which is swapped at constructor to be the best tour
    if (tours.empty()) {
        return -1;
    } else {
        return tours[0].getFitnessRating();
    }
}

// Creates a Population set to be used as a parent for
// the crossover algorithm
Population Population::makeParent() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, max-1);
    vector<Tour> parent;

    for (int i = 0; i < PARENT_POOL_SIZE; i++) {
        int index = dist(gen);
        parent.push_back(tours.at(index));
    }

    Population parentPop(masterList, parent);

    return parentPop;
}

// Crossover algorithm
void Population::crossover() {
    // Immediately return if tours is empty
    if (tours.empty()) {
        return;
    }

    // Set up random int generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, tours[0].size() - 1);

    // Initialize new vector of Tours
    // Push the elite tour to be the first Tour in the vector
    vector<Tour> newTours;
    newTours.push_back(tours[0]);

    // Crossover new Tour objects to replace this Population object's tours
    for (int i = 1; i < max; i++) {
        // Make parent Tour objects up to NUMBER_OF_PARENTS
        vector<Tour> parents;
        for (int j = 0; j < NUMBER_OF_PARENTS; j++) {
            Population parentPop = makeParent();
            Tour parentTour = parentPop.getBestTour();
            parents.push_back(parentTour);
        }

        // Keep crossing over Tour objects until finished going through
        // all the parents
        Tour crossTour(parents[0]);
        for (int j = 1; j < NUMBER_OF_PARENTS; j++) {
            Tour subTour = crossTour.copy(0, dist(gen));
            crossTour = subTour.concat(parents[j]);
        }
        newTours.push_back(crossTour);
    }
    this->setTours(newTours);
    // Remove this later
    cout << "new tours: " << *this << endl;
}

// overloaded assignment operator=
Population &Population::operator=(Population other) {
    popSwap(*this, other);
    return *this;
}

// friend function swap
void popSwap(Population &original, Population &other) {
    swap(original.masterList, other.masterList);
    swap(original.tours, other.tours);
    swap(original.max, other.max);
}

// Overloaded insertion operator prints list of Tour objects
// in Population p
ostream &operator<<(ostream &os, const Population& p) {
    for (auto ptr : p.getTours()) {
        os << ptr << endl;
    }
    os << "Best fitness rating = " << p.getBestFitnessRating() << endl;
    return os;
}
