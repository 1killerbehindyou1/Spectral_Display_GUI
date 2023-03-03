set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

# ////////////////////////// Create library witch function main()
add_library(LibraryBenchmark STATIC
    BenchmarkLibrary/main.cpp
)

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

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(LibraryBenchmarky)
    qt_finalize_executable(LibraryBenchmarky)
endif()
