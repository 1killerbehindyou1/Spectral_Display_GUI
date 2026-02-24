set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(BasicGui VERSION 0.1 LANGUAGES CXX)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(PROJECT_SOURCES
  include/LedRuler.hpp
  include/FileManager.hpp
  include/RenderSelector.hpp
  include/OutputPreview.hpp
  include/TransformEngine.hpp
  source/main.cpp
  source/LedRuler.cpp
  source/FileManager.cpp
  source/RenderSelector.cpp
  source/OutputPreview.cpp
  source/TransformEngine.cpp
  qml/qml.qrc)

add_executable(BasicGUI
  ${PROJECT_SOURCES})

target_include_directories(BasicGUI PUBLIC
  include
)

target_compile_definitions(BasicGUI
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(BasicGUI
  PUBLIC
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::QuickControls2
  QPolygonTransform
)