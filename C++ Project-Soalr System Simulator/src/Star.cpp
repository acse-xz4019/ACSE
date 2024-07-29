//
// Created by Zhang, Xiaoye on 07/03/2024.
//
#include "Star.h"
#include "ColourMap.h"

Star::Star(std::string name, std::string colour, double mass, double radius, double luminosity, const sf::VideoMode& vm, const sf::Font& font)
        : CelestialBody(std::move(name), std::move(colour), "Star", mass, radius), luminosity(luminosity){
    shape.setRadius(10);
    auto it = colourMap.find(this->colour);
    if (it != colourMap.end()) {
        shape.setFillColor(it->second);
    } else {
        shape.setFillColor(sf::Color::Yellow); // set the color of the star default to yellow
    }
    shape.setPosition(vm.width / 2 - shape.getRadius(), vm.height / 2 - shape.getRadius());

    label.setFont(font);
    label.setString(this->name); // set the label to the name of the star
    label.setCharacterSize(14); // set the font size
    label.setFillColor(sf::Color::White); // set the color of the label to white
    // set the position of the label to be at the bottom of the star
    label.setPosition(shape.getPosition().x + shape.getRadius() - label.getLocalBounds().width / 2,
                      shape.getPosition().y + 2 * shape.getRadius());
}

void Star::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(label);
}
