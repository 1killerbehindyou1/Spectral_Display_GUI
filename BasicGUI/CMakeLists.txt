set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(BasicGui VERSION 0.1 LANGUAGES CXX)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_DIR src)

set(PROJECT_SOURCES
  ${SOURCE_DIR}/Main.cpp
  QMLSources/qml.qrc
  ${SOURCE_DIR}/LedRuler.cpp
  ${SOURCE_DIR}/FileManager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(BasicGUI
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
  )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET BasicGUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
  if(ANDROID)
    add_library(BasicGUI SHARED
      ${PROJECT_SOURCES}
    )

  # Define properties for Android with Qt 5 after find_package() calls as:
  # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
  else()
    add_executable(BasicGUI
      ${PROJECT_SOURCES}
    )
  endif()
endif()

target_include_directories(BasicGUI PRIVATE
  includes
)
target_compile_definitions(BasicGUI
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(BasicGUI
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::QuickControls2

  QPolygonTransform
)

set_target_properties(BasicGUI PROPERTIES WIN32_EXECUTABLE TRUE)
