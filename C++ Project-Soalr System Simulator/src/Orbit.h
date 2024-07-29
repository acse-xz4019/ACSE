//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_ORBITMANAGER_H
#define ASSESSMENT1_ORBITMANAGER_H

#include "Planet.h"
#include <SFML/Graphics.hpp>
#include <vector>

class OrbitManager {
public:
    explicit OrbitManager(size_t planetCount); // receive the number of planets
    void updateOrbits(const std::vector<Planet>& planets); // update the orbits
    void draw(sf::RenderWindow& window); // draw the orbits

private:
    std::vector<sf::VertexArray> orbitsLines; // contains the orbits of the planets
};

#endif //ASSESSMENT1_ORBITMANAGER_H
