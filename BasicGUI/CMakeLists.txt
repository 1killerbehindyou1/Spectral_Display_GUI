set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(BasicGui VERSION 0.1 LANGUAGES CXX)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(SOURCE_DIR src)

set(PROJECT_SOURCES
  ${SOURCE_DIR}/main.cpp
  QMLSources/qml.qrc
  ${SOURCE_DIR}/LedRuler.cpp
  ${SOURCE_DIR}/FileManager.cpp
)

add_executable(BasicGUI ${PROJECT_SOURCES})

target_include_directories(BasicGUI PUBLIC includes)

target_compile_definitions(BasicGUI
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(BasicGUI
  PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::QuickControls2

  # SinglePointTransform
  QPolygonTransform
  ImageTransformCommon
)

set_target_properties(BasicGUI PROPERTIES
  WIN32_EXECUTABLE TRUE
)
