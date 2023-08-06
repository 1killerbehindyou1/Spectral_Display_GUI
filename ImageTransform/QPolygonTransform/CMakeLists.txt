set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(PROJECT_SOURCES
  src/Interpolator.cpp
)

add_library(QPolygonTransform STATIC
  ${PROJECT_SOURCES})

target_compile_definitions(QPolygonTransform
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QPolygonTransform PUBLIC

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  ImageTransformCommon
)

target_include_directories(QPolygonTransform PUBLIC
  includes
)

add_subdirectory(unit_tests)