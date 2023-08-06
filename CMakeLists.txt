cmake_minimum_required(VERSION 3.23)

project(SpectralDisplay VERSION 0.1 DESCRIPTION "General project SPRCTRAL DISPLAY" LANGUAGES CXX)

add_subdirectory(googletest)

set(CMAKE_UTILS ${CMAKE_CURRENT_SOURCE_DIR}/cmake_utils)
include(${CMAKE_UTILS}/configure_project_variables.cmake)
include(${CMAKE_UTILS}/configure_toolchain.cmake)

add_subdirectory(BasicGUI)
add_subdirectory(Benchmark)
add_subdirectory(ImageTransform)
add_subdirectory(${CMAKE_UTILS})