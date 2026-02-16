# #####################################################################################
# VARIABLES GENERAL

set(IMAGES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pictures)
set(INPUT_IMG_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/pictures/BITMAPA.png)

set(QPOLYGON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/transform_algorythms/QPolygonTransform/includes)
set(SINGLE_POINT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/transform_algorythms/SinglePointTransform/src)

set(COMMON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/transform_algorythms/common_includes)
set(GUI_SAMPLE_IMAGES_PATH ${CMAKE_SOURCE_DIR}/pictures CACHE PATH "" FORCE)

# #####################################################################################
# VARIABLES FOR COMMON PART TEST
set(GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_COMMON ${CMAKE_BINARY_DIR}/bin/UnitTests/)

# #####################################################################################
# VARIABLES FOR POLY TEST
set(GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_QPOLY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibrary CACHE PATH "" FORCE)
set(GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_QPOLY}/GeneratedPicture CACHE PATH "" FORCE)

set(GUI_COPY_IMAGES_TO_THIS_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/pictures CACHE PATH "" FORCE)
set(GUI_TESTING_IMG_QPOLY BITMAPA.png CACHE STRING "" FORCE)
file(COPY ${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}
    DESTINATION ${GUI_COPY_IMAGES_TO_THIS_PATH})

# #####################################################################################
# VARIABLES FOR SINGLE TEST
set(GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_SINGLE ${CMAKE_BINARY_DIR}/bin/UnitTests/TestSinglePointTransformLibrary CACHE PATH "" FORCE)
set(GUI_OUTPUT_GENERATED_IMG_PATH_TEST_SINGLE ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_SINGLE}/GeneratedPicture CACHE PATH "" FORCE)

set(GUI_TESTING_IMG_SINGLE BITMAPA.png CACHE STRING "" FORCE)
file(COPY ${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_SINGLE}
    DESTINATION ${GUI_COPY_IMAGES_TO_THIS_PATH})

# #####################################################################################
# VARIABLES FOR BENCHMARK
set(GUI_CMAKE_RUNTIME_OUTPUT_DIR_BENCHMARK ${CMAKE_BINARY_DIR}/bin/benchmark_test CACHE PATH "" FORCE)
set(GUI_COPY_IMAGES_TO_THIS_PATH_BENCHMARK ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_BENCHMARK}/pictures CACHE PATH "" FORCE)
set(GUI_TESTING_IMG_BENCHMARK BITMAPA.png CACHE STRING "" FORCE)

file(COPY ${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_BENCHMARK}
    DESTINATION ${GUI_COPY_IMAGES_TO_THIS_PATH_BENCHMARK})