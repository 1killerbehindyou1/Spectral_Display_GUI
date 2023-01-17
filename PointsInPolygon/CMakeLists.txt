set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(PROJECT_SOURCES
    Main.cpp
)

add_executable(PointsInPolygon ${PROJECT_SOURCES})

target_compile_definitions(PointsInPolygon
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(PointsInPolygon
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Interpolator
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(PointsInPolygon)
    qt_finalize_executable(PointsInPolygon)
endif()
