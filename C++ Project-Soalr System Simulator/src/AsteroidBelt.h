//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_ASTEROIDBELT_H
#define ASSESSMENT1_ASTEROIDBELT_H

#include <SFML/Graphics.hpp>

class AsteroidBelt {
private:
    double averageSize;
    int quantity;
    sf::VideoMode vm; // 视频模式，用于确定绘制位置
    std::vector<sf::Vector2f> positions;

public:
    double innerRadius;
    double outerRadius;
    AsteroidBelt(double innerRadius, double outerRadius, double averageSize, int quantity, sf::VideoMode vm);
    void draw(sf::RenderWindow& window, float deltaTime);
    void initializePositions(); // 初始化小行星位置
    void updatePositions(float deltaTime);
};

#endif //ASSESSMENT1_ASTEROIDBELT_H
