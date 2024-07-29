#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "Node.h"

// Class representing a mesh
class Mesh 
{
public:
    std::vector<Node> nodes;
    std::vector<double> temperatures;
    std::vector<double> pressures;

    // Constructor
    Mesh(const std::vector<Node>& _nodes,
        const std::vector<double>& _temperatures, const std::vector<double>& _pressures);
    // Display mesh information
    void displayInfo() const;
};

#endif