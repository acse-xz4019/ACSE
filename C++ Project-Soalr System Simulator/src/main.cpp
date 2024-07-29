//
// Created by Zhang, Xiaoye on 07/03/2024.
// ...with the assistance of GitHub Copilot, a code generation tool developed by GitHub and OpenAI (GitHub, 2021).
//
#include "CelestialBody.h"
#include "Planet.h"
#include "Star.h"
#include "Orbit.h"
#include "AsteroidBelt.h"
#include "Universe.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>

// astronomical unit
double AU = 149.6e6 * 1000;
// amplification factor, used to scale down the distances
double amplification = 1e-9;
// timescale factor, used to speed up the simulation
// now it is simulating 30 days in a second, alter it if you want to speed up or slow down the simulation
double timeScale = 30 * 24 * 60 * 60;
// mass scale factor, used to simplify the mass
double massScale = 1e24;

// Initialize information of the planets
std::vector<PlanetInfo> planets = {
        {"Mercury", 0.24, 0.205, 0.387 * AU * amplification},
        {"Venus", 0.615, 0.007, 0.723 * AU * amplification},
        {"Earth", 1.0, 0.017, 1.0 * AU * amplification},
        {"Mars", 1.88, 0.093, 1.524 * AU * amplification},
        {"Jupiter", 11.86, 0.049, 5.203 * AU * amplification},
        {"Saturn", 29.46, 0.057, 9.537 * AU * amplification},
        {"Uranus", 84.01, 0.046, 19.191 * AU * amplification},
        {"Neptune", 164.8, 0.010, 30.069 * AU * amplification}
};

// Define the attributes of the planets
struct PlanetAttributes {
    std::string color;
    std::string type;
    double mass;
    double radius;
};

// Initialize the attributes of the planets
std::vector<PlanetAttributes> planetAttributes = {
        {"Grey", "Terrestrial", 0.330 * massScale, 2439.7},   // Mercury
        {"Yellow", "Terrestrial", 4.87 * massScale, 6051.8},  // Venus
        {"Blue", "Terrestrial", 5.97 * massScale, 6371.0},    // Earth
        {"Red", "Terrestrial", 0.642 * massScale, 3389.5},    // Mars
        {"Brown", "Gas Giant", 1898 * massScale, 69911},      // Jupiter
        {"Yellow", "Gas Giant", 568 * massScale, 58232},      // Saturn
        {"LightBlue", "Ice Giant", 86.8 * massScale, 25362},  // Uranus
        {"DarkBlue", "Ice Giant", 102 * massScale, 24622}     // Neptune
};

int main() {
    sf::VideoMode vm(800, 600);
    sf::RenderWindow window(vm, "Planets Orbit Simulation with SFML", sf::Style::Close);
    sf::Clock clock; // Clock used to control timing and animations in the simulation
    sf::Font font; // Font for rendering text within the simulation
    if (!font.loadFromFile("../resources/Ojuju/Ojuju-VariableFont_wght.ttf")) {
        return -1;
    }

    // Preparing options for user interaction before the simulation starts
    sf::Text title("Choose a mode to display the Solar System", font, 30);
    title.setPosition(vm.width/2 - 250, vm.height/2 - 100);
    sf::Text textMode1("Display Text", font, 20);
    textMode1.setPosition(vm.width/2 - 50, vm.height/2 + 20);
    sf::Text textMode2("Display Animation", font, 20);
    textMode2.setPosition(vm.width/2 - 50, vm.height/2 + 80);


    // create a universe object to hold the star and planets
    // Although the concept of this class is to integrate all celestial bodies into a unified environment,
    // based on the provided information, its main role seems to be limited to storing and setting celestial objects.
    // Without more complex functionalities, such as managing interactions between celestial bodies or offering more methods
    // to manage the state of the entire universe, it might be considered relatively "under-developed".
    Universe universe;

    // create a star object and add it to the universe
    // Even though the Star class indeed provides basic drawing functionality and some foundational attributes (like luminosity),
    // it might fall short in simulating all the possible features and
    // behaviors of a star compared to actual stellar physical characteristics (such as a star's lifecycle, spectral type, etc.).
    auto sun = std::make_shared<Star>("Sun", "Orange", 1.989e6 * massScale, 696340, 3.828e26, vm, font);
    universe.setStar(sun);

    // create a vector of planet objects and add them to the universe
    // The Planet class appears to be more "well-developed" as it includes not only basic attributes of a planet (such as name, color, type, mass, and radius)
    // but also implements functionality to update the planet's position according to Kepler's laws of motion.
    // Moreover, it has methods for drawing the planet and its associated text label, providing a visual representation in the simulation.
    std::vector<Planet> planetsVector;
    planetsVector.reserve(planets.size());
    for (size_t i = 0; i < planets.size(); ++i) {
        const auto& planetInfo = planets[i];
        const auto& attrs = planetAttributes[i];
        auto planet = std::make_shared<Planet>(planetInfo.name, attrs.color, attrs.type, attrs.mass, attrs.radius, planetInfo.T, planetInfo.e, planetInfo.a, font);
        planetsVector.push_back(*planet);
        universe.addPlanet(planet);
    }

    // create an orbitManager object to hold the orbits of the planets
    // The orbitManager class manages the orbits of planets,
    // updating orbits based on the dynamic positions of the planets and drawing these orbits in the graphical interface.
    // This indicates it is relatively well-developed in terms of handling complex logic and visual representation.
    OrbitManager orbitManager(planets.size());

    // create an asteroid belt object and add it to the universe
    // The AsteroidBelt class appears to be well-developed, as it includes functionality to update the position of the asteroids and draw them in the simulation.
    // By defining the inner radius, outer radius, average size, and quantity of the asteroid belt, and providing drawing functionality,
    // this class adds additional complexity and visual layers to the simulation, making it another more complete object.
    auto aBelt = std::make_shared<AsteroidBelt>(2.2 * AU * amplification, 3.3 * AU * amplification, 2, 100, vm);
    universe.setAsteroidBelt(aBelt);

    // the options for the user to choose between text and animation
    bool displayTextInfo = false;
    bool waitingForChoice = true;
    bool isDragging = false;
    sf::Vector2f dragStartPoint;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // monitor the mouse wheel event to zoom in and out
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    float zoomAmount = 1.1f; // default zoom amount
                    sf::View view = window.getView(); // get the current view

                    if (event.mouseWheelScroll.delta > 0) {
                        // scroll up, zoom out
                        view.zoom(1 / zoomAmount);
                    } else if (event.mouseWheelScroll.delta < 0) {
                        // scroll down, zoom in
                        view.zoom(zoomAmount);
                    }

                    window.setView(view); // update the view
                }
            }

            // press and hold the left mouse button to drag the view
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = true;
                    // record the start position of the drag
                    dragStartPoint = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
            }

            // deal with the mouse release event
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                }
            }

            // deal with the mouse move event
            if (event.type == sf::Event::MouseMoved && isDragging) {
                // current position of the mouse
                sf::Vector2f currentPoint = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // calculate the offset
                sf::Vector2f offset = dragStartPoint - currentPoint;

                // get the current view
                sf::View view = window.getView();
                // move the view
                view.move(offset);
                window.setView(view);

                // update the start point for the next drag
                dragStartPoint = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            }

            // if the user has not made a choice, listen for the user's choice
            if (waitingForChoice && event.type == sf::Event::MouseButtonPressed) {
                if (textMode1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    displayTextInfo = true; // user has chosen to display text
                    waitingForChoice = false; // user has made a choice
                    clock.restart();
                }
                if (textMode2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    displayTextInfo = false; // user has chosen to display animation
                    waitingForChoice = false; // user has made a choice
                    clock.restart();
                }
            }
        }

        window.clear(); // Clearing the window for the next frame
        if (waitingForChoice) {
            // if the user has not made a choice, display the options
            window.draw(title);
            window.draw(textMode1);
            window.draw(textMode2);
        } else {
        if (displayTextInfo) {
            // if the user has chosen to display text, display the information of the star, planets and asteroid belt
            sf::Text consoleOutput;
            consoleOutput.setFont(font);           // set the font
            consoleOutput.setCharacterSize(20);    // set the character size
            consoleOutput.setPosition(20, 20);     // set the position
            consoleOutput.setString(universe.printSystemInfo() + Universe::printAsteroidBeltLocation(planetsVector, *aBelt));
            window.draw(consoleOutput);
        } else {
            sf::Text instructionText;
            instructionText.setFont(font);
            instructionText.setString("Scroll: Zoom view\nLeft-click drag: Move view");
            instructionText.setCharacterSize(20); // Set font size
            instructionText.setFillColor(sf::Color::White); // Set font color
            // Get the current view
            const sf::View& currentView = window.getView();

            // Calculate new position for the instruction text (10 pixels from the top-left corner of the view)
            sf::Vector2f newTextPosition = currentView.getCenter() - 0.5f * currentView.getSize() + sf::Vector2f(10, 10);

            // Update the text's position
            instructionText.setPosition(newTextPosition);
            // if the user has chosen to display animation, draw the star and planets
            sun->draw(window);

            double elapsedTime = clock.getElapsedTime().asSeconds() * timeScale; // apply the timescale

            // update the position of each planet and draw it
            for (auto &planet: planetsVector) {
                planet.updatePosition(elapsedTime, vm);
                planet.draw(window); // draw the planet
            }
            // based on the updated position of each planet, update the orbits and draw them
            orbitManager.updateOrbits(planetsVector);
            orbitManager.draw(window); // draw the orbits

            // draw the asteroid belt
            float deltaTime = clock.getElapsedTime().asSeconds();
            AsteroidBelt asteroidBelt(2.2 * AU * amplification, 3.3 * AU * amplification, 2, 100, vm);
            asteroidBelt.draw(window, deltaTime);
            sf::Text abeltText;
            abeltText.setFont(font);
            abeltText.setString("Astroid Belt");
            abeltText.setCharacterSize(20); // Set font size
            abeltText.setFillColor(sf::Color::White); // Set font color
            abeltText.setPosition(vm.width / 2 - asteroidBelt.outerRadius, vm.height / 2);


            window.draw(abeltText);
            window.draw(instructionText);
            }
        }
        window.display();
    }

    return 0;
}
