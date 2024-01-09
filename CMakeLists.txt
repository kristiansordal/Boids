cmake_minimum_required(VERSION 3.15)

project(Boids
    VERSION 0.1.0
    DESCRIPTION "Boids simulation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -ffast-math")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(boids 
    src/Entity.hpp
    src/Entity.cpp
    src/Boid.hpp
    src/Boid.cpp
    src/Flock.hpp
    src/Flock.cpp
    src/Solver.hpp
    src/Solver.cpp
    src/main.cpp
)


target_include_directories(boids PRIVATE ${SFML_INCLUDE_DIR})
target_compile_options(boids PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(boids PRIVATE sfml-system sfml-window sfml-graphics)

set(CMAKE_COLOR_DIAGNOSTIC ON)
