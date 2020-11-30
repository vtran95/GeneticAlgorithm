//
// Created by Vincent on 2020-11-23.
//

#include <iomanip>
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
ostream &operator<<(ostream &os, const City& city) {
    os << "City " << setw(2) << city.getId() << ", x: " << setw(7) << fixed << setprecision(3)
       << city.getX() << ", y: " << setw(7) << city.getY() << endl;
    return os;
}