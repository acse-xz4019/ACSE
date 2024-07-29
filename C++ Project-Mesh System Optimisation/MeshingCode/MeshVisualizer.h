//
// Created by Zhang, Xiaoye on 13/03/2024.
//

#ifndef ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_MESHVISUALIZER_H
#define ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_MESHVISUALIZER_H

#include <SFML/Graphics.hpp>
#include "Mesh.h"
namespace MeshVisualizer {

    // function to draw a mesh with custom color and transparency
    void drawMesh(const Mesh& mesh, sf::RenderWindow& window, sf::Color color, float scaleFactor, unsigned int alpha) {
        color.a = alpha; // set the alpha value of the color, 0 is fully transparent, 255 is fully opaque
        for (const auto & node : mesh.nodes) {
            sf::CircleShape circle(5); // create a circle with radius 5
            circle.setFillColor(color); // set the fill color of the circle
            circle.setPosition(node.x * scaleFactor - 5, node.y * scaleFactor - 5);
            window.draw(circle);
        }
    }

    // function to visualize two meshes with custom colors and transparency
    void visualizeMeshes(const Mesh& sourceMesh, const Mesh& targetMesh, float scaleFactor, sf::Color sourceColor, sf::Color targetColor, unsigned int sourceAlpha, unsigned int targetAlpha) {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Mesh Visualization with Custom Colors and Transparency");
        // create a window with size 800x600 and title "Mesh Visualization with Custom Colors and Transparency"
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Black); // use black color to clear the window

            // plot the source and target meshes, with custom colors and transparency
            drawMesh(sourceMesh, window, sourceColor, scaleFactor, sourceAlpha);
            drawMesh(targetMesh, window, targetColor, scaleFactor, targetAlpha);

            window.display();
        }
    }


} // namespace MeshVisualizer

#endif //ADVANCED_PROGRAMMING_ASSESSMENT_2_ACSE_XZ4019_MESHVISUALIZER_H
