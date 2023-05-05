find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../Pictures/BITMAPA.png
  DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/)

add_custom_target(build-time-make-directory ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/UnitTests/GeneratedPicture)

add_executable(InterpolatorTest
  InterpolatorTest.cpp
)

target_include_directories(InterpolatorTest
  PUBLIC ../src
)

target_compile_definitions(InterpolatorTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(InterpolatorTest
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

# ######################################################################
add_executable(TransformationTest
  TransformationTest.cpp
)

target_include_directories(TransformationTest
  PUBLIC ../src
)

target_compile_definitions(TransformationTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(TransformationTest
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)