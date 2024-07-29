cmake_minimum_required(VERSION 3.27)
project(assessment1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# search for SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(assessment1
        src/calculation.h
        src/Planet.h
        src/Star.h
        src/AsteroidBelt.h
        src/Universe.h
        src/CelestialBody.h
        src/main.cpp
        src/Planet.cpp
        src/Star.cpp
        src/Orbit.h
        src/Orbit.cpp
        src/calculation.cpp
        src/ColourMap.h
        src/AsteroidBelt.cpp
        src/Universe.cpp
)

# link SFML
target_link_libraries(assessment1 sfml-graphics sfml-audio)

