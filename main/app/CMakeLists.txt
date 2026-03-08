set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(BasicGui VERSION 0.1 LANGUAGES CXX)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Network Qml QmlModels Quick QuickControls2)
include(GNUInstallDirs)

set(PROJECT_SOURCES
  include/RenderEngine.hpp
  include/FileManager.hpp
  include/SettingsManager.hpp
  include/RenderSelector.hpp
  include/LiveImageProvider.hpp
  include/TransformEngine.hpp
  include/ProcessMonitor.hpp
  source/main.cpp
  source/RenderEngine.cpp
  source/FileManager.cpp
  source/SettingsManager.cpp
  source/RenderSelector.cpp
  source/LiveImageProvider.cpp
  source/TransformEngine.cpp
  source/ProcessMonitor.cpp
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
  SinglePointTransform
)

install(TARGETS BasicGUI RUNTIME DESTINATION . )

set_target_properties(BasicGUI PROPERTIES
  INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
)

set(QT_QMAKE_TARGET "Qt${QT_VERSION_MAJOR}::qmake")
set(QT_PLUGINS_DIR "")
set(QT_QML_DIR "")

if(TARGET ${QT_QMAKE_TARGET})
  get_target_property(QT_QMAKE_EXECUTABLE ${QT_QMAKE_TARGET} IMPORTED_LOCATION)
  if(QT_QMAKE_EXECUTABLE)
    execute_process(
      COMMAND "${QT_QMAKE_EXECUTABLE}" -query QT_INSTALL_PLUGINS
      OUTPUT_VARIABLE QT_PLUGINS_DIR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
      COMMAND "${QT_QMAKE_EXECUTABLE}" -query QT_INSTALL_QML
      OUTPUT_VARIABLE QT_QML_DIR
      OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  endif()
endif()

set(QT_CONF_FILE "${CMAKE_CURRENT_BINARY_DIR}/qt.conf")
file(WRITE "${QT_CONF_FILE}" "[Paths]\nPrefix=..\nLibraries=lib\nPlugins=plugins\nQml2Imports=qml\n")

install(FILES "${QT_CONF_FILE}" DESTINATION .)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION .)

install(PROGRAMS
  "${CMAKE_SOURCE_DIR}/scripts/run_portable.sh"
  "${CMAKE_SOURCE_DIR}/scripts/run_portable_debug.sh"
  DESTINATION scripts
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/documentation/source_images" DESTINATION example_images)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/documentation/architecture" DESTINATION architecture)


set(QT_RUNTIME_TARGETS
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Qml
  Qt${QT_VERSION_MAJOR}::QmlModels
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::QuickControls2
)

foreach(qt_runtime_target IN LISTS QT_RUNTIME_TARGETS)
  if(TARGET ${qt_runtime_target})
    install(FILES
      $<TARGET_FILE:${qt_runtime_target}>
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
  endif()
endforeach()

if(QT_PLUGINS_DIR)
  install(DIRECTORY "${QT_PLUGINS_DIR}/platforms" DESTINATION plugins OPTIONAL)
  install(DIRECTORY "${QT_PLUGINS_DIR}/imageformats" DESTINATION plugins OPTIONAL)
  install(DIRECTORY "${QT_PLUGINS_DIR}/platformthemes" DESTINATION plugins OPTIONAL)
  install(DIRECTORY "${QT_PLUGINS_DIR}/xcbglintegrations" DESTINATION plugins OPTIONAL)
endif()

if(QT_QML_DIR)
  install(DIRECTORY "${QT_QML_DIR}/" DESTINATION qml OPTIONAL)
endif()

# install(CODE [[
#   set(archive_items
#     README.md
#     bin/BasicGui
#     lib
#     plugins
#     documentation/architecture
#     documentation/source_images
#     scripts/run_portable.sh
#     scripts/run_portable_debug.sh
#     json_schema
#     project_configuration
#   )

#   execute_process(
#     COMMAND "${CMAKE_COMMAND}" -E tar "cfvz" "${archive_path}" --format=gnutar -- ${existing_items}
#     WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}"
#     RESULT_VARIABLE archive_result
#     OUTPUT_VARIABLE archive_stdout
#     ERROR_VARIABLE archive_stderr
#   )

#   if(NOT archive_result EQUAL 0)
#     message(FATAL_ERROR "Failed to create install archive: ${archive_stderr}")
#   endif()

#   message(STATUS "Created portable archive: ${archive_path}")
# ]])