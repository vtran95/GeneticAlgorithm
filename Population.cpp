//
// Created by Vincent on 2020-11-25.
//

#include "Population.hpp"

Population::Population(vector<City> cities, int max) : masterList(cities), max(max) {
    for (int i = 0; i < max; i++) {
        Tour t(masterList);
        tours.push_back(t);
    }
    moveEliteToFront();
}

Population::Population(vector<City> masterList, vector<Tour> t) {
    this->masterList = masterList;
    this->tours = t;
    this->max = t.size();
    moveEliteToFront();
}

Population::Population(const Population &copy_pop) {
    masterList = copy_pop.masterList;
    tours = copy_pop.getTours();
    max = copy_pop.getTours().size();
    moveEliteToFront();
}

Population::~Population() {
    tours.clear();
}

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

vector<Tour> Population::getTours() const {
    return tours;
}

Tour Population::getAt(int index) const {
    return tours[index];
}

Tour Population::getBestTour() const {
    return tours[0];
}

double Population::getBestFitnessRating() const {
    // Return -1 if tours is empty, else return the tour in the front
    // which is swapped at constructor to be the best tour
    if (tours.empty()) {
        return -1;
    } else {
        return tours[0].getFitnessRating();
    }
}

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

void Population::crossover() {
    // Immediately return if tours is empty
    if (tours.empty()) {
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, tours[0].size() - 1);

    vector<Tour> newTours;
    newTours.push_back(tours[0]);

    for (int i = 1; i < max; i++) {
        Population parent1 = makeParent();
        Population parent2 = makeParent();
        Tour tour1 = parent1.getBestTour();
        Tour tour2 = parent2.getBestTour();

        Tour subTour1 = tour1.copy(0, dist(gen));

        Tour crossTour = subTour1.concat(tour2);
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

// Overloaded insertion operator prints list of City objects pointed to in Tour
ostream &operator<<(ostream &os, const Population& p) {
    for (auto ptr : p.getTours()) {
        os << ptr << endl;
    }
    os << "Best fitness rating = " << p.getBestFitnessRating() << endl;
    return os;
}
