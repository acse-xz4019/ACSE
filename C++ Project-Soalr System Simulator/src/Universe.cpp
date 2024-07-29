//
// Created by Zhang, Xiaoye on 08/03/2024.
//

#include "Universe.h"
#include <iostream>
#include <sstream>

double amplification_ = 1e-9;

std::string Universe::printSystemInfo() const {
    std::stringstream outputStream;
    // print star information
    if (star) {
        outputStream << "Star Name: " << star->name << ", Colour: " << star->colour
                  << ", Mass: " << star->mass << "kg, Radius: " << star->radius
                  << "km, Luminosity: " << star->luminosity << "Watts\n" <<std::endl;
    }

    // print planet information
    for (const auto& planet : planets) {
        outputStream << "Planet Name: " << planet->name << ", Colour: " << planet->colour
                  << ", Type: " << planet->type << ", Mass: " << planet->mass
                  << "kg, Radius: " << planet->radius << "km\n" <<std::endl;
    }

    // print asteroid belt information
    if (asteroidBelt) {
        outputStream << "Asteroid Belt inner radius: " << asteroidBelt->innerRadius / (amplification_*1000)<< "km, outer radius: " << asteroidBelt->outerRadius / (amplification_*1000)
                     <<  "km\n" <<std::endl;
    }

    return outputStream.str();
}
std::string Universe::printAsteroidBeltLocation(const std::vector<Planet>& planets, const AsteroidBelt& asteroidBelt) {
    std::stringstream outputStream;
    std::vector<Planet> sortedPlanets(planets);
    std::sort(sortedPlanets.begin(), sortedPlanets.end(), [](const Planet& a, const Planet& b) {
        return a.info.a < b.info.a;
    });

    // 查找小行星带位置
    double asteroidBeltRadius = asteroidBelt.innerRadius;
    for (size_t i = 0; i < sortedPlanets.size() - 1; ++i) {
        if (sortedPlanets[i].info.a < asteroidBeltRadius &&
            sortedPlanets[i + 1].info.a > asteroidBeltRadius) {
            outputStream << "The Asteroid Belt is between " << sortedPlanets[i].name << " and " << sortedPlanets[i + 1].name << ".\n";
            break;
        }
    }
    return outputStream.str();
}