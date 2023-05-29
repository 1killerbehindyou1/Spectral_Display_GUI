set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Benchmark)

find_package(QT NAMES Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../Pictures/BITMAPA.png
    DESTINATION ${CMAKE_BINARY_DIR}/bin/Benchmark/Pictures/)

add_custom_target(build-time-make-directory-bench ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/Benchmark)

# ////////////////////////// Create library witch function main()
add_library(LibraryBenchmark STATIC
    BenchmarkLibrary/main.cpp
    BenchmarkLibrary/MeasurementTools.cpp
)
target_include_directories(LibraryBenchmark PUBLIC BenchmarkLibrary/public)

target_compile_definitions(LibraryBenchmark
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(LibraryBenchmark
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)

# //////////////// Create executable to benchmark SinglePointTransform library
add_executable(SinglePointBenchmark
    SinglePointBenchmark/SinglePointTask.cpp
)

target_compile_definitions(SinglePointBenchmark
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(SinglePointBenchmark
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    SinglePointTransform
    LibraryBenchmark
)

target_include_directories(SinglePointBenchmark
    PUBLIC ../SinglePointTransform_lib/src
)

# /////////////// Create executable to benchmark QPolygonTransform library
add_executable(QPolygonBenchmark
    QPolygonBenchmark/QPolygonTask.cpp
)

target_compile_definitions(QPolygonBenchmark
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QPolygonBenchmark
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    QPolygonTransform
    LibraryBenchmark
)
target_include_directories(QPolygonBenchmark
    PUBLIC ../QPolygonTransform_lib/src
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(LibraryBenchmarky)
    qt_finalize_executable(LibraryBenchmarky)
endif()
