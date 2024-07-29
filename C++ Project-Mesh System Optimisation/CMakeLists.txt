cmake_minimum_required(VERSION 3.27)
project(advanced_programming_assessment_2_acse_xz4019)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# search for SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
# search for Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

#include_directories(MeshingCode)

add_executable(advanced_programming_assessment_2_acse_xz4019
#        MeshingCode/Element.h
        MeshingCode/main.cpp
        MeshingCode/Mesh.cpp
        MeshingCode/Mesh.h
        MeshingCode/MeshMapper.cpp
        MeshingCode/MeshMapper.h
        MeshingCode/Node.h
        MeshingCode/DataFrame.h
        MeshingCode/MeshVisualizer.h
        MeshingCode/Octree.h
        MeshingCode/Octree.cpp
)

# link SFML
target_link_libraries(advanced_programming_assessment_2_acse_xz4019 sfml-graphics sfml-audio)
# link Eigen
target_link_libraries(advanced_programming_assessment_2_acse_xz4019 Eigen3::Eigen)