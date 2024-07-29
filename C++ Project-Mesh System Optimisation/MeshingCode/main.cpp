#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <fstream>

#include "Node.h"
#include "Element.h"
#include "Mesh.h"
#include "MeshMapper.h"
#include "DataFrame.h"
#include "MeshVisualizer.h"

std::string file1 = "../dataset/source.csv";
std::string file2 = "../dataset/target.csv";
std::string file3 = "../dataset/groundtruth.csv";
DataFrame df1; // DataFrame is a class that reads CSV files
DataFrame df2; // you need to initialise a dataframe object and use it to read a specific CSV file
DataFrame df3; // If you reuse the same dataframe object to read multiple files, the data from the previous file will not be cleared
std::vector<Node> sourceNodes;
std::vector<double> sourceTemperatures, sourcePressures;

std::vector<Node> targetNodes;
std::vector<double> targetTemperatures, targetPressures;

std::vector<Node> groundtruthNodes;
std::vector<double> groundtruthTemperatures, groundtruthPressures;

// calculate the mapping error by mapping the source mesh to the target mesh and then back to the source mesh
// then compare the original source mesh and the reverse-mapped source mesh
std::pair<double, double> TestMeshMappingError(const Mesh& originalSourceMesh, Mesh& targetMesh) {
    // First, map from source to target
    MeshMapper::MapMeshValues(originalSourceMesh, targetMesh);

    // Create a mesh to hold the reverse-mapped values
    Mesh reverseMappedSource = originalSourceMesh; // Initialize with original source structure, but values will be overwritten

    // Now, map back from target to this new source mesh
    MeshMapper::MapMeshValues(targetMesh, reverseMappedSource);

    // Compare the original source mesh and the reverse-mapped source mesh
    double temError = 0.0;
    double presError = 0.0;
    for (size_t i = 0; i < originalSourceMesh.nodes.size(); ++i) {
        // Calculate the relative error for each node
        double errorTemperature = std::abs(originalSourceMesh.temperatures[i] - reverseMappedSource.temperatures[i])/std::abs(originalSourceMesh.temperatures[i]);
        double errorPressure = std::abs(originalSourceMesh.pressures[i] - reverseMappedSource.pressures[i])/std::abs(originalSourceMesh.pressures[i]);

        temError += errorTemperature;
        presError += errorPressure;
    }
    temError /= originalSourceMesh.nodes.size();
    presError /= originalSourceMesh.nodes.size();
    std::cout << "Average mapping error (temperature): " << temError << std::endl;
    std::cout << "Average mapping error (pressure): " << presError << std::endl;

    return {temError, presError};
}

// calculate the mapping error by mapping the source mesh to the target mesh and then compare the target mesh with the ground truth
std::pair<double, double> TestMeshMappingError_withgroundtruth(const Mesh& groundtruth, Mesh& prediction){
    double temError = 0.0;
    double presError = 0.0;
    for (size_t i = 0; i < groundtruth.nodes.size(); ++i) {
        // Calculate the relative error for each node
        double errorTemperature = std::abs(groundtruth.temperatures[i] - prediction.temperatures[i])/std::abs(groundtruth.temperatures[i]);
        double errorPressure = std::abs(groundtruth.pressures[i] - prediction.pressures[i])/std::abs(groundtruth.pressures[i]);

        temError += errorTemperature;
        presError += errorPressure;
    }
    temError /= groundtruth.nodes.size();
    presError /= groundtruth.nodes.size();
    std::cout << "Average mapping error (temperature): " << temError << std::endl;
    std::cout << "Average mapping error (pressure): " << presError << std::endl;

    return {temError, presError};
}


int main()
{
    auto sourcedf = df1.readCSV(file1, ',', false);
    for (const auto& row : sourcedf) {
        sourceNodes.emplace_back(row[0], row[1], row[2]);
        sourceTemperatures.push_back(row[3]);
        sourcePressures.push_back(row[4]);
    }

    auto targetdf = df2.readCSV(file2, ',', false);
    for (const auto& row : targetdf) {
        targetNodes.emplace_back(row[0], row[1], row[2]);
        targetTemperatures.push_back(row[3]);
        targetPressures.push_back(row[4]);
    }

    auto groundtruthdf = df3.readCSV(file3, ',', false);
    for (const auto& row : groundtruthdf) {
        groundtruthNodes.emplace_back(row[0], row[1], row[2]);
        groundtruthTemperatures.push_back(row[3]);
        groundtruthPressures.push_back(row[4]);
    }
    Mesh groundtruthMesh(groundtruthNodes, groundtruthTemperatures, groundtruthPressures);

    // Start the timer
    std::clock_t start = std::clock();

    // create source and target meshes
    Mesh sourceMesh(sourceNodes, sourceTemperatures, sourcePressures);
    Mesh targetMesh(targetNodes, targetTemperatures, targetPressures);

    // Map values from the source mesh to the target mesh using isogeometric linear triangles
    MeshMapper::MapMeshValues(sourceMesh, targetMesh);

    // Stop the timer and calculate the elapsed time
    std::clock_t end = std::clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << " seconds.\n";

    float scaleFactor = 5.0;
    sf::Color sourceMeshColor = sf::Color::Red;
    sf::Color targetMeshColor = sf::Color::Green;

    unsigned int sourceAlpha = 255; // fully opaque
    unsigned int targetAlpha = 128; // half transparent

    // Visualize the source and target meshes
//    MeshVisualizer::visualizeMeshes(sourceMesh, targetMesh, scaleFactor, sourceMeshColor, targetMeshColor, sourceAlpha, targetAlpha);

    // Test the mapping error
//    std::pair<double, double> map2error = TestMeshMappingError(sourceMesh, targetMesh);
    std::pair<double, double> absoluteError =TestMeshMappingError_withgroundtruth(groundtruthMesh, targetMesh);

    // Open a file in write mode
    std::ofstream outputFile("../output.csv", std::ios::app);

    // Check if the file is open
    if (outputFile.is_open()) {
        // Write the metrics to the file
        // Assuming you want to output the size of targetNodes, mapError's both values, absoluteError's both values, and elapsed time
        outputFile << targetNodes.size() << ","
//                   << map2error.first << "," << map2error.second << ","
                   << absoluteError.first << "," << absoluteError.second << ","
                   << elapsed << "\n";

        // Close the file
        outputFile.close();
    } else {
        std::cerr << "Failed to open file for output.\n";
    }
    return 0;
}
