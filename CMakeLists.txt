cmake_minimum_required(VERSION 3.23)

project(SpectralDisplay VERSION 0.1 DESCRIPTION "General project SPRCTRAL DISPLAY" LANGUAGES CXX)

set(CMAKE_UTILS ${CMAKE_CURRENT_SOURCE_DIR}/utils/cmake_utils)

include(${CMAKE_UTILS}/configure_project_variables.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib_static)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION_MAJOR 5)

option(BUILD_UT "Build unit tests" OFF)
option(BUILD_BENCHMARK_TESTS "Build benchmark tests" OFF)

if(BUILD_UT)
    include(CTest)
    enable_testing()
    add_subdirectory(depend/googletest)
    add_subdirectory(utils/googletest_utils)
    add_subdirectory(tests)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(main)





