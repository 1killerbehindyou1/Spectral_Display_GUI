set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

add_library(QPolygonTransform STATIC
  src/Interpolator.cpp
  src/Transformation.cpp)

target_compile_definitions(QPolygonTransform
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QPolygonTransform
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::QuickControls2
)
target_include_directories(QPolygonTransform PUBLIC
  ${COMMON_HEADERS}
  includes
)

add_subdirectory(unit_tests)