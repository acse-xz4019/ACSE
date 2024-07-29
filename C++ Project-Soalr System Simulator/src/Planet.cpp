//
// Created by Zhang, Xiaoye on 07/03/2024.
//
#include "Planet.h"
#include "calculation.h"
# include "ColourMap.h"
#include <tuple>

Planet::Planet(std::string name, std::string colour, std::string type, double mass, double radius,
               double T, double e, double a, const sf::Font& font)
        : CelestialBody(std::move(name), std::move(colour), std::move(type), mass, radius),
          info({std::move(name), T, e, a}) {
    shape.setRadius(5);
    auto it = colourMap.find(this->colour);
    if (it != colourMap.end()) {
        shape.setFillColor(it->second);
    } else {
        shape.setFillColor(sf::Color::Green); // set the color of the planet default to green
    }

    legend.setFont(font);
    legend.setString(this->name);
    legend.setCharacterSize(12);
    legend.setFillColor(sf::Color::White);
}

void Planet::updatePosition(double elapsedTime, const sf::VideoMode& vm) {
    auto [x, y] = planet_position(elapsedTime, info.T * 365.25 * 24 * 60 * 60, info.e, info.a);
    shape.setPosition(vm.width / 2 + x - shape.getRadius(), vm.height / 2 + y - shape.getRadius());
    legend.setPosition(shape.getPosition().x + 10, shape.getPosition().y);
}


void Planet::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(legend);
}

sf::Vector2f Planet::getPosition() const {
    // get the position of the planet
    return {shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()};
}