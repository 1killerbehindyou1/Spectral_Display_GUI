set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(PROJECT_SOURCES
  src/Interpolator.cpp
  src/Transformation.cpp
)

add_library(ImageTransformCommon STATIC
  ${PROJECT_SOURCES})

target_compile_definitions(ImageTransformCommon
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(ImageTransformCommon
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::QuickControls2
)
target_include_directories(ImageTransformCommon PUBLIC
  includes
)