//
// Created by Zhang, Xiaoye on 08/03/2024.
//
#include "AsteroidBelt.h"
#include <random>

AsteroidBelt::AsteroidBelt(double innerRadius, double outerRadius, double averageSize, int quantity, sf::VideoMode vm)
    : innerRadius(innerRadius), outerRadius(outerRadius), averageSize(averageSize), quantity(quantity), vm(vm) {
    initializePositions();
}

void AsteroidBelt::initializePositions() {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_real_distribution<double> distanceDistribution(innerRadius, outerRadius);
    std::uniform_real_distribution<double> angleDistribution(0.0, 2 * M_PI);

    positions.clear();
    for (int i = 0; i < quantity; ++i) {
        double distance = distanceDistribution(generator);
        double angle = angleDistribution(generator);
        positions.emplace_back(distance * cos(angle), distance * sin(angle));
    }
}

void AsteroidBelt::updatePositions(float deltaTime) {
    std::default_random_engine generator(std::random_device{}());
    std::normal_distribution<double> offsetDistribution(0.0, (averageSize / 5) * deltaTime); // 控制移动范围

    for (auto& position : positions) {
        position.x += offsetDistribution(generator);
        position.y += offsetDistribution(generator);
        // 确保位置更新不会导致小行星离开设定的内外半径范围
        double distance = sqrt(position.x * position.x + position.y * position.y);
        if (distance < innerRadius || distance > outerRadius) {
            position.x -= 2 * offsetDistribution(generator); // 简单的反向移动
            position.y -= 2 * offsetDistribution(generator);
        }
    }
}

void AsteroidBelt::draw(sf::RenderWindow& window, float deltaTime) {
    updatePositions(deltaTime); // 每次绘制前更新位置，实现动态效果

    for (const auto& position : positions) {
        sf::CircleShape asteroid(averageSize);
        asteroid.setPosition(position.x + vm.width / 2 - asteroid.getRadius(), position.y + vm.height / 2 - asteroid.getRadius());
        asteroid.setFillColor(sf::Color::White); // 可以使用 ColourMap 选择颜色
        window.draw(asteroid);
    }
}