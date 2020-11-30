//
// Created by Vincent on 2020-11-25.
//

#include "Population.hpp"

// Constructor that creates a vector of Tour objects with size max
Population::Population(vector<City> cities, int max) : masterList(cities), max(max), eliteIterFlag(false) {
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
    this->eliteIterFlag = false;
    moveEliteToFront();
}

// Copy constructor
Population::Population(const Population &copy_pop) {
    masterList = copy_pop.masterList;
    tours = copy_pop.getTours();
    max = copy_pop.getTours().size();
    eliteIter = copy_pop.eliteIter;
    eliteIterFlag = copy_pop.eliteIterFlag;
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

    // Find the Tour with the best fitness rating, and the iterator
    // pointing towards it
    setEliteIter();

    // swap the first tour with the tour with best fitness
    iter_swap(tours.begin(), eliteIter);

    // Re-assign eliteIter to the Tour at the start
    eliteIter = tours.begin();
}

// Return all Tours
vector<Tour> Population::getTours() const {
    return tours;
}

// Set new tours for this Population
void Population::setTours(vector<Tour> t) {
    tours = t;
}

Tour Population::getAt(int index) const {
    return tours[index];
}

// Returns the best tour, else if it has not been set, throw an error
Tour Population::getBestTour() const {
    if (eliteIterFlag) {
        return *eliteIter;
    } else {
        throw invalid_argument("Iterator for Best Tour has not been set.");
    }
}

// Returns the best fitness rating, else if it has not been set, throw an error
double Population::getBestFitnessRating() const {
    if (eliteIterFlag) {
        return (*eliteIter).getFitnessRating();
    } else {
        throw invalid_argument("Iterator for Best Tour has not been set.");
    }
}

// Determines the Tour with the best fitness rating and sets an iterator pointing to it
// Return true if a new iterator is set, else return false if it's the same or empty
bool Population::setEliteIter() {
    // Return -1 if tours is empty, else return the tour in the front
    // which is swapped at constructor to be the best tour
    if (tours.empty()) {
        return false;
    } else {
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

        // Assign true to signal that the iterator has been set
        eliteIterFlag = true;

        // Check if eliteIter already is pointing to the Tour with best fitness
        if (eliteIter == bestIter) {
            return false;
        } else {
            // Assign the iterator pointing to the Tour with best fitness to eliteIter
            eliteIter = bestIter;
            return true;
        }

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
}

// Mutate each tour in the Population
void Population::mutate(double rate) {
    // Immediately return if tours is empty
    if (tours.empty()) {
        return;
    }

    // Mutate each tour, except for the elite tour (the first one)
    for (auto it = next(tours.begin()); it != tours.end(); ++it ) {
        (*it).mutateCities(rate);
    }
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
