//
// Created by Zhang, Xiaoye on 13/03/2024.
//
#include "Octree.h"

// calculateBounds: calculate the bounds of a set of nodes
std::pair<Node, Node> Octree::calculateBounds(const std::vector<Node>& nodes) {
    if (nodes.empty()) return {Node(0, 0, 0), Node(0, 0, 0)};

    Node minBounds = nodes[0];
    Node maxBounds = nodes[0];

    for (const auto& node : nodes) {
        minBounds.x = std::min(minBounds.x, node.x);
        minBounds.y = std::min(minBounds.y, node.y);
        minBounds.z = std::min(minBounds.z, node.z);

        maxBounds.x = std::max(maxBounds.x, node.x);
        maxBounds.y = std::max(maxBounds.y, node.y);
        maxBounds.z = std::max(maxBounds.z, node.z);
    }

    return {minBounds, maxBounds};
}

// Octree constructor
Octree::Octree(const Node& minBounds, const Node& maxBounds) : minBounds(minBounds), maxBounds(maxBounds) {
    root = std::make_unique<OctreeNode>(minBounds, maxBounds);
}

// insert: insert a point into the octree
void Octree::insert(const Node *point) {
    insertRecursively(root, const_cast<Node *>(point), minBounds, maxBounds);
}

// insertRecursively: insert a point into the octree recursively
int Octree::getOctantContainingPoint(const Node& point, const Node& center) {
    int octant = 0;
    if (point.x >= center.x) octant |= 4;
    if (point.y >= center.y) octant |= 2;
    if (point.z >= center.z) octant |= 1;
    return octant;
}

// createChildren: create children for a node
void Octree::createChildren(const std::unique_ptr<OctreeNode>& node, const Node& min, const Node& max) {
    Node center = {(min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2};

    for (int i = 0; i < 8; i++) {
        Node childMin = min, childMax = max;

        if (i & 4) {
            childMin.x = center.x;
        } else {
            childMax.x = center.x;
        }

        if (i & 2) {
            childMin.y = center.y;
        } else {
            childMax.y = center.y;
        }

        if (i & 1) {
            childMin.z = center.z;
        } else {
            childMax.z = center.z;
        }
        // create a new child node, and assign it to the children array
        node->children[i] = std::make_unique<OctreeNode>(childMin, childMax);
    }

    // the node is no longer a leaf node
    node->isLeaf = false;
}

// adjustChildBounds: adjust the bounds of a child node
void Octree::adjustChildBounds(int octant, Node& childMin, Node& childMax, const Node& center) {
    if (octant & 4) childMin.x = center.x; else childMax.x = center.x;
    if (octant & 2) childMin.y = center.y; else childMax.y = center.y;
    if (octant & 1) childMin.z = center.z; else childMax.z = center.z;
}

// insertRecursively: insert a point into the octree recursively
void Octree::insertRecursively(const std::unique_ptr<OctreeNode>& node, Node* point, const Node& min, const Node& max) {
    if (node->isLeaf) {
        if (!node->point) {
            node->point = point;
        } else {
            // the node already contains a point, we need to create children
            Node* existingPoint = node->point;
            node->point = nullptr;
            createChildren(node, min, max);
            node->isLeaf = false;

            // insert the existing point into the children
            insertRecursively(node, existingPoint, min, max);
            insertRecursively(node, point, min, max);
        }
    } else {
        // the node is an internal node, insert the point into the appropriate child
        int octant = getOctantContainingPoint(*point, calculateCenter(min, max));
        Node childMin = min, childMax = max;
        adjustChildBounds(octant, childMin, childMax, calculateCenter(min, max));
        if (!node->children[octant]) {
            // the child does not exist, create it
            node->children[octant] = std::make_unique<OctreeNode>(childMin, childMax);
        }

        // insert the point into the child
        insertRecursively(node->children[octant], point, childMin, childMax);
    }
}

// calculateCenter: calculate the center of the bounds
Node Octree::calculateCenter(const Node& minBounds, const Node& maxBounds) {
    return {(minBounds.x + maxBounds.x) / 2, (minBounds.y + maxBounds.y) / 2, (minBounds.z + maxBounds.z) / 2};
}

// findNearest: find the nearest node to the target node
void Octree::findKNearestRec(const std::unique_ptr<OctreeNode>& node, const Node& target, int k, std::priority_queue<std::pair<double, Node*>>& pq) const {
    if (!node) return;

    // calculate the minimum distance to the target
    double minDistToTarget = node->minDistanceTo(target);

    // if the priority queue is full and the minimum distance is larger than the largest distance in the queue, do not search this node
    if (pq.size() == k && minDistToTarget > pq.top().first) {
        return;
    }

    // if the node is a leaf node, calculate the distance to the target and update the priority queue
    if (node->isLeaf && node->point) {
        double dist = Node::distance(*node->point, target);
        if (pq.size() < k || dist < pq.top().first) {
            pq.push(std::make_pair(dist, node->point));
            if (pq.size() > k) {
                pq.pop();
            }
        }
    } else {
        // if the node is not a leaf node, search its children
        for (const auto& child : node->children) {
            if (child) {
                findKNearestRec(child, target, k, pq);
            }
        }
    }
}

// findKNearest: find the k nearest nodes to the target node
void Octree::findKNearest(const Node& target, int k, std::vector<Node*>& nearestNodes) const {
    std::priority_queue<std::pair<double, Node*>> pq; // Max heap by distance
    findKNearestRec(root, target, k, pq);

    nearestNodes.clear();
    while (!pq.empty()) {
        nearestNodes.push_back(pq.top().second); // The second element of the pair is the node pointer
        pq.pop();
    }
    std::reverse(nearestNodes.begin(), nearestNodes.end()); // Optional, to have closest first
}