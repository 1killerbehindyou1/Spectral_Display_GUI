set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(QPolygonTransform STATIC
  src/InterpolatorQPoly.cpp)

target_compile_definitions(QPolygonTransform
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QPolygonTransform
  PUBLIC
  BaseInterpolation
)

target_include_directories(QPolygonTransform PUBLIC
  src
)

add_subdirectory(unit_tests)