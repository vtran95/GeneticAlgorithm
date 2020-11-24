//
// Created by Vincent on 2020-11-24.
//

#ifndef GENETICALGORITHM_CITYGENERATOR_HPP
#define GENETICALGORITHM_CITYGENERATOR_HPP

#include <vector>
#include <random>
#include "City.hpp"

#define XY_MIN 0.0
#define XY_MAX 1000.0

// Class for generating the master list of City objects
class CityGenerator {
public:
    // Generate a vector list of up to n random City objects
    vector<City> createList(double n);
};

#endif //GENETICALGORITHM_CITYGENERATOR_HPP
