set(GUI_COPY_IMAGES_TO_THIS_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures CACHE PATH "" FORCE)
set(GUI_SAMPLE_IMAGES_PATH ${CMAKE_SOURCE_DIR}/Pictures CACHE PATH "" FORCE)
set(GUI_TESTING_IMG BITMAPA.png CACHE STRING "" FORCE)
set(GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_QPOLY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibrary CACHE PATH "" FORCE)
set(GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_QPOLY}/GeneratedPicture CACHE PATH "" FORCE)

set(GUI_CMAKE_RUNTIME_OUTPUT_DIR_BENCHMARK ${CMAKE_BINARY_DIR}/bin/Benchmark CACHE PATH "" FORCE)
set(GUI_COPY_IMAGES_TO_THIS_PATH_BENCHMARK ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_BENCHMARK}/Pictures CACHE PATH "" FORCE)

file(COPY ${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG}
    DESTINATION ${GUI_COPY_IMAGES_TO_THIS_PATH})

file(COPY ${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG}
    DESTINATION ${GUI_COPY_IMAGES_TO_THIS_PATH_BENCHMARK})