cmake_minimum_required(VERSION 3.23)

project(SpectralDisplay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

add_subdirectory(BasicGUI)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/PointsInPoligon)

add_subdirectory(PointsInPoligon)

