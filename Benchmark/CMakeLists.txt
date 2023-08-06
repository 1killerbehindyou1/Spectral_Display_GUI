project(SpectralDisplay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Benchmark)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../Pictures/BITMAPA.png
    DESTINATION ${CMAKE_BINARY_DIR}/bin/Benchmark/Pictures/)

add_custom_target(make_directory_benchmark ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Benchmark)

add_subdirectory(BenchmarkLibrary)
add_subdirectory(QPolygonBenchmark)
add_subdirectory(SinglePointBenchmark)