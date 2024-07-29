#ifndef NODE_H
#define NODE_H

#include <vector>

// Class representing a node in the mesh
class Node {
public:
    double x, y, z;
    Node(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    // calculate the distance between two nodes
    static double distance(const Node& a, const Node& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
    }

    // Define equality operator for Node
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y && z == other.z;}
};

#endif