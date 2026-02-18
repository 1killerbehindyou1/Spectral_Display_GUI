set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(BasicGui VERSION 0.1 LANGUAGES CXX)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(PROJECT_SOURCES
  src/main.cpp
  src/LedRuler.cpp
  src/FileManager.cpp
  src/RenderSelector.cpp
  qml/qml.qrc)

add_executable(BasicGUI
  ${PROJECT_SOURCES})

target_include_directories(BasicGUI PUBLIC
  src
)

target_compile_definitions(BasicGUI
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(BasicGUI
  PUBLIC
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::QuickControls2
  QPolygonTransform
)