cmake_minimum_required(VERSION 3.23)

project(SpectralDisplay VERSION 0.1 DESCRIPTION "General project SPRCTRAL DISPLAY" LANGUAGES CXX)

set(CMAKE_UTILS ${CMAKE_CURRENT_SOURCE_DIR}/cmake_utils)

#include(${CMAKE_UTILS}/configure_toolchain.cmake)
include(${CMAKE_UTILS}/configure_project_variables.cmake)
add_subdirectory(${CMAKE_UTILS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib_static)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION_MAJOR 5)

# ######################################################
# VARIABLES DEFINITION
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib_static)

set(IMAGES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Pictures)
set(INPUT_IMG_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/BITMAPA.png)

set(QPOLYGON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Transform_algorythms/QPolygonTransform/includes)
set(SINGLE_POINT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Transform_algorythms/SinglePointTransform/src)

set(COMMON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Transform_algorythms/common_includes)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(ImageTransform)
add_subdirectory(Transform_algorythms)
add_subdirectory(Pictures)
add_subdirectory(BasicGUI)

if(BUILD_UT)
    include(CTest)
    enable_testing()
    set(_saved_autouic ${CMAKE_AUTOUIC})
    set(_saved_automoc ${CMAKE_AUTOMOC})
    set(_saved_autorcc ${CMAKE_AUTORCC})
    set(CMAKE_AUTOUIC OFF)
    set(CMAKE_AUTOMOC OFF)
    set(CMAKE_AUTORCC OFF)
    add_subdirectory(depend/googletest)
    add_subdirectory(googletest_utils)
    set(CMAKE_AUTOUIC ${_saved_autouic})
    set(CMAKE_AUTOMOC ${_saved_automoc})
    set(CMAKE_AUTORCC ${_saved_autorcc})
endif()

if(BUILD_BENCHMARK_TESTS)
    add_subdirectory(Benchmark)
endif()


