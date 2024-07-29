//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_PLANET_H
#define ASSESSMENT1_PLANET_H
#include "CelestialBody.h"
#include <SFML/Graphics.hpp>

struct PlanetInfo {
    std::string name;
    double T; // period
    double e; // eccentricity
    double a; // semi-major axis
};

class Planet : public CelestialBody {
public:
    PlanetInfo info;
    sf::CircleShape shape;
    sf::Text legend;

    Planet(std::string name, std::string colour, std::string type, double mass, double radius,
           double T, double e, double a, const sf::Font& font);

    void updatePosition(double elapsedTime, const sf::VideoMode& vm);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
};
#endif //ASSESSMENT1_PLANET_H
