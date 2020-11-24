//
// Created by Vincent on 2020-11-23.
//

#include "City.hpp"

// Constructor for setting name, x-coordinate, and y-coordinate
City::City(int id, double x, double y) : id(id), x(x), y(y) {}

// Getter for city name
const int City::getId() const {
    return id;
}

// Getter for city x-coordinate
double City::getX() const {
    return x;
}

// Getter for city y-coordinate
double City::getY() const {
    return y;
}

// Overloaded insertion operator prints description of City
std::ostream &operator<<(ostream &os, const City& city) {
    os << "City " << city.getId() << ", x: " << city.getX() << ", y: " << city.getY() << endl;
    return os;
}