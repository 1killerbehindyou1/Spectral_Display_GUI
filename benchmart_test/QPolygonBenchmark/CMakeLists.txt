set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_executable(QPolygonBenchmark
    QPolygonTask.cpp
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
    PUBLIC ${QPOLYGON_INCLUDE_DIR}
)
