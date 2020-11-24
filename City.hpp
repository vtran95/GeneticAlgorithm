//
// Created by Vincent on 2020-11-23.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <iostream>

using namespace std;

// City class with name and coordinates
class City {
    int id;
    double x;
    double y;

public:
    // Constructor for setting name, x-coordinate, and y-coordinate
    City(int id, double x, double y);

    // Getter for city name
    const int getId() const;

    // Getter for city x-coordinate
    double getX() const;

    // Getter for city y-coordinate
    double getY() const;

    // Overloaded insertion operator for printing to ostream
    friend ostream& operator<<(ostream& os, const City& city);
};

#endif //GENETICALGORITHM_CITY_HPP
