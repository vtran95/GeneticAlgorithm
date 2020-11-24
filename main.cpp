#include <iostream>
#include "CityGenerator.hpp"
#include "Tour.hpp"

#define CITIES_IN_TOUR 32

int main() {
    CityGenerator gen;
    vector<City> masterList = gen.createList(CITIES_IN_TOUR);

    for (auto it = masterList.begin(); it != masterList.end(); ++it) {
        cout << *it;
    }

    Tour tour1(masterList);

    cout << endl << tour1;

    return 0;
}
