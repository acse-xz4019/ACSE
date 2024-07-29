//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_STAR_H
#define ASSESSMENT1_STAR_H
#include "CelestialBody.h"
#include <SFML/Graphics.hpp>
class Star : public CelestialBody {
public:
    double luminosity;
    sf::CircleShape shape;
    sf::Text label;

    Star(std::string name, std::string colour, double mass, double radius, double luminosity, const sf::VideoMode& vm, const sf::Font& font);

    void draw(sf::RenderWindow& window) const;
};

#endif //ASSESSMENT1_STAR_H
