#ifndef MESHMAPPER_H
#define MESHMAPPER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <Eigen/Dense>

#include "Node.h"
#include "Element.h"
#include "Mesh.h"

double gaussianRBF(const Node& n1, const Node& n2, double epsilon = 1e-3); //epsilon controls the smoothness of the RBF


// Class representing a mesh mapper
class MeshMapper {
public:
    // Barycentric interpolation within a triangle
//    static void BarycentricInterpolation(
//            const Node& p, const Node& p0, const Node& p1, const Node& p2,
//            double& w0, double& w1, double& w2);

    // Map values from one mesh to another using isogeometric linear triangles
    static void MapMeshValues(const Mesh& sourceMesh, Mesh& targetMesh);

    // RBF interpolation
    static double RBFInterpolate(
            const std::vector<Node>& sourceNodes,
            const std::vector<double>& sourceValues,
            const Node targetNodes);

private:
};

#endif
