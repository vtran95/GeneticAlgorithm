//
// Created by Vincent on 2020-11-23.
//

#include "City.hpp"

// Constructor for setting name, x-coordinate, and y-coordinate
City::City(string name, int x, int y) : name(name), x(x), y(y) {}

// Getter for city name
const string City::getName() const {
    return name;
}

// Getter for city x-coordinate
int City::getX() const {
    return x;
}

// Getter for city y-coordinate
int City::getY() const {
    return y;
}

// Overloaded insertion operator prints description of City
std::ostream &operator<<(ostream &os, const City& city) {
    os << "City: " << city.getName() << ", x: " << city.getX() << ", y: " << city.getY() << endl;
    return os;
}