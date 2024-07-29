//
// Created by Zhang, Xiaoye on 08/03/2024.
//

#ifndef ASSESSMENT1_COLOURMAP_H
#define ASSESSMENT1_COLOURMAP_H
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

// define a map to store the colour of the planets
static const std::unordered_map<std::string, sf::Color> colourMap = {
        {"Red", sf::Color::Red},
        {"Green", sf::Color::Green},
        {"Blue", sf::Color::Blue},
        {"LightBlue", sf::Color(173, 216, 230)},
        {"DarkBlue", sf::Color(0, 0, 139)},
        {"Yellow", sf::Color::Yellow},
        {"White", sf::Color::White},
        {"Grey", sf::Color(128, 128, 128)},
        {"Cyan", sf::Color::Cyan},
        {"Magenta", sf::Color::Magenta},
        {"Transparent", sf::Color::Transparent},
        {"Black", sf::Color::Black},
        {"Brown", sf::Color(165, 42, 42)},
        {"Orange", sf::Color(255, 165, 0)},
        {"Pink", sf::Color(255, 192, 203)},
        {"Purple", sf::Color(128, 0, 128)},
        {"Gold", sf::Color(255, 215, 0)},
        {"Silver", sf::Color(192, 192, 192)},
        {"Bronze", sf::Color(205, 127, 50)},
        {"Maroon", sf::Color(128, 0, 0)},
        {"Olive", sf::Color(128, 128, 0)},
        {"Teal", sf::Color(0, 128, 128)},
        {"Navy", sf::Color(0, 0, 128)}
        // add more colour as you need
};
#endif //ASSESSMENT1_COLOURMAP_H
