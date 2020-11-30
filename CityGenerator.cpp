//
// Created by Vincent on 2020-11-24.
//

#include "CityGenerator.hpp"

// Creates a master list of cities with random distances
// for the x and y values
vector<City> CityGenerator::createList(double n) {
    // Random double generator from XY_MIN to XY_MAX
    default_random_engine gen(time(0));
    uniform_real_distribution<double> dist(XY_MIN, XY_MAX);

    // Vector to hold the City objects
    vector<City> cities;

    // Create n City objects with random x and y values
    for (int i = 0; i < n; i++) {
        City city(i, dist(gen), dist(gen));
        cities.push_back(city);
    }

    return cities;
}