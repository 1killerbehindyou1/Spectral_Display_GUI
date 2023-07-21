find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestQPolygonTransformLibrary)
set(INPUT_IMG_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/BITMAPA.png)
set(OUTPUT_IMG_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GeneratedPicture)

add_custom_target(build-time-make-directory-qpoly ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_polygon_ruler_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_bounding_rect_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_polygon_contains_point
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_library
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_color)

file(COPY ${IMAGE_TESTED_SRC_PATH}
  DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/)

# ///////////////////////////////INTERPOLATOR TEST////////////////////////////////
add_executable(Unit_test_Interpolator_qpoly
  InterpolatorTest.cpp
)
target_compile_definitions(Unit_test_Interpolator_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_test_Interpolator_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform
  ImageTransformCommon

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)
target_compile_definitions(Unit_test_Interpolator_qpoly PRIVATE
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

# ############################TRANSFORMATION TEST##############################
add_executable(Unit_test_Transformation_qpoly
  TransformationTest.cpp
)

target_compile_definitions(Unit_test_Transformation_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_test_Transformation_qpoly
  PUBLIC
  gtest_main
  gmock
  ImageTransformCommon
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

# #############################LIBRARY TEST#################################
add_executable(Unit_test_QPolygonTransform_lib_qpoly
  QPolygonTransform_libTest.cpp
)

target_compile_definitions(Unit_test_QPolygonTransform_lib_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_test_QPolygonTransform_lib_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  # ImageTransformCommon
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)
target_compile_definitions(Unit_test_QPolygonTransform_lib_qpoly PRIVATE
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

# ############################COLORINTERPOLTEST TEST##############################
add_executable(Unit_test_ColorInterpolation
  Unit_test_ColorInterpolation.cpp
)

target_compile_definitions(Unit_test_ColorInterpolation
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_test_ColorInterpolation
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform
  ImageTransformCommon

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

target_compile_definitions(Unit_test_ColorInterpolation PRIVATE
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)
