project(SpectralDisplay VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_BENCHMARK})

add_subdirectory(BenchmarkLibrary)
add_subdirectory(QPolygonBenchmark)
add_subdirectory(SinglePointBenchmark)