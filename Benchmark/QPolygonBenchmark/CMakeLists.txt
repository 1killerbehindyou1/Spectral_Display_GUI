set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_executable(QPolygonBenchmark
    QPolygonTask.cpp
)

target_compile_definitions(QPolygonBenchmark
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QPolygonBenchmark
    PRIVATE
    QPolygonTransform
    LibraryBenchmark
)
