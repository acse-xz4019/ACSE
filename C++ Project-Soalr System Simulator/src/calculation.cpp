//
// Created by Zhang, Xiaoye on 07/03/2024.
//
#include "calculation.h"

double solve_kepler(double M, double e, double tol) {
    double E = M;
    double delta;
    do {
        delta = E - e * std::sin(E) - M;
        E -= delta / (1 - e * std::cos(E));
    } while (std::abs(delta) > tol);
    return E;
}

std::pair<double, double> planet_position(double t, double T, double e, double a) {
    double M = 2 * M_PI * std::fmod(t, T) / T;
    double E = solve_kepler(M, e);
    double x = a * (std::cos(E) - e);
    double y = a * std::sqrt(1 - e * e) * std::sin(E);
    return {x, y};
}
