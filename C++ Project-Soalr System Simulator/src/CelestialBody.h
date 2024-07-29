//
// Created by Zhang, Xiaoye on 07/03/2024.
//

#ifndef ASSESSMENT1_CELESTIALBODY_H
#define ASSESSMENT1_CELESTIALBODY_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class CelestialBody {
public:
    std::string name;
    std::string colour; // 颜色
    std::string type;
    double mass; // 质量
    double radius; // 半径，单位为千米

    // Modify the constructor to take strings by value and use std::move to initialize members
    CelestialBody(std::string name, std::string colour, std::string type, double mass, double radius)
            : name(std::move(name)), colour(std::move(colour)), type(std::move(type)), mass(mass), radius(radius) {}

    // 虚析构函数确保派生类的正确析构
    virtual ~CelestialBody() = default;
};

#endif //ASSESSMENT1_CELESTIALBODY_H
