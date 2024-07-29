#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

// Class representing an element in the mesh
class Element {
public:
    std::vector<int> nodeIndices;
    explicit Element(const std::vector<int>& indices) : nodeIndices(indices) {}
};

#endif