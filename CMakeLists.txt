cmake_minimum_required(VERSION 3.22)
project(2x2RubikSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(2x2RubikSolver
        main.cpp
        src/cube_solver.cpp
        src/utils.cpp
        src/Cube.cpp)
