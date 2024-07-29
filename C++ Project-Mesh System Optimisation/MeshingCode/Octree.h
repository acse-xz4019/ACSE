//
// Created by Zhang, Xiaoye on 13/03/2024.
//

#ifndef ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_OCTREE_H
#define ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_OCTREE_H
#include <array>
#include <memory>
#include <queue>
#include "Node.h"

class OctreeNode {
public:
    std::array<std::unique_ptr<OctreeNode>, 8> children; // eight children
    bool isLeaf = true; // whether the node is a leaf
    Node* point = nullptr; // initially, the node does not contain any point
    Node minBounds, maxBounds; // the bounds of the node
    OctreeNode() = default;
    // constructor for a leaf node
    OctreeNode(const Node& minBounds, const Node& maxBounds)
            : minBounds(minBounds), maxBounds(maxBounds), isLeaf(true), point(nullptr) {}

    // a method to calculate the distance between the query node and the bounds of the node
    double minDistanceTo(const Node& query) const {
        double dx = std::max(0.0, std::max(minBounds.x - query.x, query.x - maxBounds.x));
        double dy = std::max(0.0, std::max(minBounds.y - query.y, query.y - maxBounds.y));
        double dz = std::max(0.0, std::max(minBounds.z - query.z, query.z - maxBounds.z));
        return std::sqrt(dx*dx + dy*dy + dz*dz);
    }
};

class Octree {
private:
    std::unique_ptr<OctreeNode> root; // the root of the octree, most time it represent the whole tree
    Node minBounds, maxBounds; // the bounds of the octree

    // a method to insert a point into the octree
    void insertRecursively(const std::unique_ptr<OctreeNode>& node, Node* point, const Node& min, const Node& max);

    // a method to find the octant containing the point
    static int getOctantContainingPoint(const Node& point, const Node& center) ;

    // a method to adjust the bounds of the child node
    static void adjustChildBounds(int octant, Node &childMin, Node &childMax, const Node &center);

    // a method to create the children of the node
    static void createChildren(const std::unique_ptr<OctreeNode> &node, const Node &min, const Node &max);

    // a method to calculate the centre of the bounds
    [[nodiscard]] static Node calculateCenter(const Node &minBounds, const Node &maxBounds) ;

    // a method to find the k nearest nodes to the target node
    void findKNearestRec(const std::unique_ptr<OctreeNode>& node, const Node& target, int k, std::priority_queue<std::pair<double, Node*>>& pq) const;

public:
    // constructor for the octree
    Octree(const Node& minBounds, const Node& maxBounds);

    // a method to insert a point into the octree
    void insert(const Node *point);

    // a method to calculate the bounds of the octree
    static std::pair<Node, Node> calculateBounds(const std::vector<Node>& nodes);

    // a method to find the nearest k nodes to the target node
    void findKNearest(const Node& target, int k, std::vector<Node*>& nearestNodes) const;


};
#endif //ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_OCTREE_H
