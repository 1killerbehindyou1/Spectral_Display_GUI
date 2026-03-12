cmake_minimum_required(VERSION 3.28)

project(SpectralDisplay VERSION 0.1 DESCRIPTION "General project SPRCTRAL DISPLAY" LANGUAGES CXX)

include(GNUInstallDirs)

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
option(BUILD_DOCUMENTATION "Generate API documentation with Doxygen" OFF)

if(BUILD_DOCUMENTATION)
    find_package(Doxygen QUIET)

    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR
            "BUILD_DOCUMENTATION=ON requires Doxygen, but the 'doxygen' executable was not found. "
            "Install it first, for example on Ubuntu/Debian: sudo apt install doxygen"
        )
    endif()

    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_FILE_PATTERNS *.hpp)
    set(DOXYGEN_INPUT_DIRS
        ${CMAKE_SOURCE_DIR}/main/app/include
        ${CMAKE_SOURCE_DIR}/main/transform_algorythms/common/InterpolationCore
        ${CMAKE_SOURCE_DIR}/main/transform_algorythms/common/TransformationCore
        ${CMAKE_SOURCE_DIR}/main/transform_algorythms/SinglePointTransform
        ${CMAKE_SOURCE_DIR}/main/transform_algorythms/QPolygonTransform
    )
    set(DOXYGEN_EXCLUDE_DIRS
        ${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/depend
        ${CMAKE_SOURCE_DIR}/utils/googletest_utils
        ${CMAKE_SOURCE_DIR}/documentation/qml_example
    )

    string(JOIN " " DOXYGEN_INPUTS ${DOXYGEN_INPUT_DIRS})
    string(JOIN " " DOXYGEN_EXCLUDES ${DOXYGEN_EXCLUDE_DIRS})

    configure_file(
        ${CMAKE_SOURCE_DIR}/documentation/Doxyfile.in
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
    )

    add_custom_target(DoxygenDoc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

    install(DIRECTORY "${DOXYGEN_OUTPUT_DIR}/"
        DESTINATION documentation
        OPTIONAL
    )

endif()

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




