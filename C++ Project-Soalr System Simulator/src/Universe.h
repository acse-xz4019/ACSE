//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_UNIVERSE_H
#define ASSESSMENT1_UNIVERSE_H
#include "Planet.h"
#include "Star.h"
#include "AsteroidBelt.h"
#include <iostream>

class Universe {
private:
    std::vector<std::shared_ptr<Planet>> planets;
    std::shared_ptr<Star> star;
    std::shared_ptr<AsteroidBelt> asteroidBelt;

public:
    void addPlanet(const std::shared_ptr<Planet>& planet) {
        planets.push_back(planet);
    }

    void setStar(const std::shared_ptr<Star>& star) {
        this->star = star;
    }

    void setAsteroidBelt(const std::shared_ptr<AsteroidBelt>& asteroidBelt) {
        this->asteroidBelt = asteroidBelt;
    }

    static std::string printAsteroidBeltLocation(const std::vector<Planet>& planets, const AsteroidBelt& asteroidBelt);

    [[nodiscard]] std::string printSystemInfo() const;
};
#endif //ASSESSMENT1_UNIVERSE_H
