set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(BasicGui VERSION 0.1 LANGUAGES CXX)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick QuickControls2)
set(SOURCE_DIR src)

set(PROJECT_SOURCES
  ${SOURCE_DIR}/main.cpp
  ${SOURCE_DIR}/Controller.cpp
  QMLSources/qml.qrc
)

add_executable(gui_with_threading ${PROJECT_SOURCES})

target_include_directories(gui_with_threading PUBLIC src)

target_compile_definitions(gui_with_threading
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(gui_with_threading
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::QuickControls2
)

set_target_properties(gui_with_threading PROPERTIES
  WIN32_EXECUTABLE TRUE
)
