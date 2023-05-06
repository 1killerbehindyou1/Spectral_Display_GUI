find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibibrary)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../Pictures/BITMAPA.png
  DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/)

add_custom_target(build-time-make-directory-qpoly ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibibrary/GeneratedPicture/test_polygon_ruler_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibibrary/GeneratedPicture/test_bounding_rect_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibibrary/GeneratedPicture/test_polygon_contains_point
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibibrary/GeneratedPicture/test_library)

add_executable(InterpolatorTest_qpoly
  InterpolatorTest.cpp
)

target_include_directories(InterpolatorTest_qpoly
  PUBLIC ../src
)

target_compile_definitions(InterpolatorTest_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(InterpolatorTest_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

# ############################TRANSFORMATION TEST##############################
add_executable(TransformationTest_qpoly
  TransformationTest.cpp
)

target_include_directories(TransformationTest_qpoly
  PUBLIC ../src
)

target_compile_definitions(TransformationTest_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(TransformationTest_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

# #############################LIBRARY TEST#################################
add_executable(QPolygonTransform_libTest_qpoly
  QPolygonTransform_libTest.cpp
)

target_include_directories(QPolygonTransform_libTest_qpoly
  PUBLIC ../src
)

target_compile_definitions(QPolygonTransform_libTest_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(QPolygonTransform_libTest_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)