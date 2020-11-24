//
// Created by Vincent on 2020-11-23.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <iostream>

using namespace std;

// City class with name and coordinates
class City {
    string name;
    int x;
    int y;

public:
    // Constructor for setting name, x-coordinate, and y-coordinate
    City(string name, int x, int y);

    // Getter for city name
    const string getName() const;

    // Getter for city x-coordinate
    int getX() const;

    // Getter for city y-coordinate
    int getY() const;

    // Overloaded insertion operator for printing to ostream
    friend ostream& operator<<(ostream& os, const City& city);
};

#endif //GENETICALGORITHM_CITY_HPP
