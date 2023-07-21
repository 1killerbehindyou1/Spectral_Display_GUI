set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)

set(PROJECT_SOURCES
  src/Transformation.cpp
  src/ColorCalc.cpp
)

add_library(ImageTransformCommon STATIC
  ${PROJECT_SOURCES})

target_compile_definitions(ImageTransformCommon
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(ImageTransformCommon PRIVATE
  Qt${QT_VERSION_MAJOR}::Gui
)

target_include_directories(ImageTransformCommon PUBLIC
  includes
)