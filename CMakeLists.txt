cmake_minimum_required(VERSION 3.17)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -W")

add_executable(GeneticAlgorithm main.cpp City.cpp City.hpp CityGenerator.cpp CityGenerator.hpp Tour.cpp Tour.hpp Population.cpp Population.hpp)