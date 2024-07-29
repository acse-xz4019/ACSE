#include "MeshMapper.h"
#include "Octree.h"
#include <cmath>
#include <limits>
#include <algorithm>

// define the gaussian RBF for interpolation
double gaussianRBF(const Node& n1, const Node& n2, double epsilon) {
    double distance = sqrt(pow(n1.x - n2.x, 2) + pow(n1.y - n2.y, 2) + pow(n1.z - n2.z, 2));
    return exp(-epsilon * distance * distance);
}

Octree octree();
int k = 10; // the number of nearest nodes to search for interpolation

// Barycentric interpolation within a triangle
//void MeshMapper::BarycentricInterpolation(
//        const Node& p, const Node& p0, const Node& p1, const Node& p2,
//        double& w0, double& w1, double& w2)
//{
//    double detT = (p1.y - p2.y) * (p0.x - p2.x) + (p2.x - p1.x) * (p0.y - p2.y);
//    w0 = ((p1.y - p2.y) * (p.x - p2.x) + (p2.x - p1.x) * (p.y - p2.y)) / detT;
//    w1 = ((p2.y - p0.y) * (p.x - p2.x) + (p0.x - p2.x) * (p.y - p2.y)) / detT;
//    w2 = 1.0 - w0 - w1;
//}

//define the RBF interpolation function
double MeshMapper::RBFInterpolate(
        const std::vector<Node>& sourceNodes,
        const std::vector<double>& sourceValues,
        const Node targetNodes) {

    double targetValues = 0.0;

    // use Eigen library to solve the linear system
    Eigen::MatrixXd A(sourceNodes.size(), sourceNodes.size());
    Eigen::VectorXd b(sourceValues.size());

    // build the linear system for Ax = b
    for (int i = 0; i < sourceNodes.size(); ++i) {
        b(i) = sourceValues[i];
        for (int j = 0; j < sourceNodes.size(); ++j) {
            A(i, j) = gaussianRBF(sourceNodes[i], sourceNodes[j]);
        }
    }

    // solve the linear system to get the coefficients
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

    // use the coefficients to interpolate the target value
    for (int j = 0; j < sourceNodes.size(); ++j) {
        targetValues += x(j) * gaussianRBF(targetNodes, sourceNodes[j]);
    }
    return targetValues;
}


// Map values from one mesh to another using isogeometric linear triangles
void MeshMapper::MapMeshValues(const Mesh& sourceMesh, Mesh& targetMesh) {
    // resize targetMesh.temperatures and targetMesh.pressures
    targetMesh.temperatures.resize(targetMesh.nodes.size());
    targetMesh.pressures.resize(targetMesh.nodes.size());

    // build the octree for the source mesh
    auto [minBounds, maxBounds] = Octree::calculateBounds(sourceMesh.nodes);
    Octree octree(minBounds, maxBounds);

    // Insert each node of the source mesh into the Octree
    for (const auto& node : sourceMesh.nodes) {
        octree.insert(&node);
    }

    // search for the k nearest nodes for each node in the target mesh
    for (auto& targetNode : targetMesh.nodes) {
        std::vector<Node*> kNearestNodes;
        octree.findKNearest(targetNode, k, kNearestNodes);
        //apply RBF interpolation with the k nearest nodes
        std::vector<Node> kNearestNodesCopy;
        int targetIndex;
        targetIndex =
                std::find(targetMesh.nodes.begin(), targetMesh.nodes.end(), targetNode) - targetMesh.nodes.begin();
        kNearestNodesCopy.reserve(kNearestNodes.size()); // reserve memory for the k nearest nodes
        std::vector<double> kNearestTemperatures;
        kNearestTemperatures.reserve(kNearestNodes.size()); // reserve memory for the k nearest nodes' temperatures
        std::vector<double> kNearestPressures;
        kNearestPressures.reserve(kNearestNodes.size()); // reserve memory for the k nearest nodes' pressures
        int KNN_index;
    for (auto node : kNearestNodes) {
        KNN_index = std::find(sourceMesh.nodes.begin(), sourceMesh.nodes.end(), *node) - sourceMesh.nodes.begin();
        kNearestNodesCopy.push_back(*node); // copy the k nearest nodes
        kNearestTemperatures.push_back(sourceMesh.temperatures[KNN_index]); // copy the k nearest nodes' temperatures
        kNearestPressures.push_back(sourceMesh.pressures[KNN_index]); // copy the k nearest nodes' pressures
        }

    // apply RBF interpolation to get the interpolated temperature and pressure
    targetMesh.temperatures[targetIndex] = RBFInterpolate(kNearestNodesCopy, kNearestTemperatures, targetNode);
    targetMesh.pressures[targetIndex] = RBFInterpolate(kNearestNodesCopy, kNearestPressures, targetNode);


    }

}