cmake_minimum_required(VERSION 3.13)
project(qps)

set(CMAKE_CXX_STANDARD 14)

add_executable(qps main.cpp mazeToGraph.h mazeToGraph.cpp graphToPath.h graphToPath.cpp floodFill.h floodFill.cpp)
