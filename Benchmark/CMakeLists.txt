add_subdirectory(SinglePointBenchmark)
add_subdirectory(QPolygonBenchmark)
add_subdirectory(BenchmarkLibrary)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Benchmark)
set(QPOLYGON_INCLUDE_DIR ${ROOT_PROJECT_PATH}/Transform_liraries/QPolygonTransform/src)

add_custom_target(make-directory-benchmark ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Benchmark)

file(COPY ${TEST_BITMAP_LOCATION}
    DESTINATION ${CMAKE_BINARY_DIR}/bin/Benchmark/Pictures/)
