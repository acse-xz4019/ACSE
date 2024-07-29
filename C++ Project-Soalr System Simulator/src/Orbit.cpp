//
// Created by Zhang, Xiaoye on 07/03/2024.
//
#include "Orbit.h"
#include "calculation.h" // If needed for additional calculations

OrbitManager::OrbitManager(size_t planetCount) {
    // Initialize orbitsLines with empty VertexArrays for each planet
    orbitsLines.resize(planetCount, sf::VertexArray(sf::LinesStrip));
}

void OrbitManager::updateOrbits(const std::vector<Planet>& planets) {
    for (size_t i = 0; i < planets.size(); ++i) {
        sf::Vector2f position = planets[i].getPosition();
        if (!orbitsLines[i].getVertexCount() || orbitsLines[i][orbitsLines[i].getVertexCount() - 1].position != position) {
            orbitsLines[i].append(sf::Vertex(position, sf::Color::White));
        }
    }
}

void OrbitManager::draw(sf::RenderWindow& window) {
    for (const auto& line : orbitsLines) {
        window.draw(line);
    }
}