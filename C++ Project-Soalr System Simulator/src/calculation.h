//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_CALCULATION_H
#define ASSESSMENT1_CALCULATION_H
#include <cmath>
#include <utility> // For std::pair
#include <vector>

// use newton-raphson method to solve kepler's equation
double solve_kepler(double M, double e, double tol = 1e-15);

// calculate the position of a planet at time t
std::pair<double, double> planet_position(double t, double T, double e, double a);

#endif //ASSESSMENT1_CALCULATION_H
