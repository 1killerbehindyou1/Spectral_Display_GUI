find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_QPOLY})

add_custom_target(build-time-make-directory-qpoly ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_polygon_ruler_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_bounding_rect_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_polygon_contains_point
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_library
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_color)

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
)
target_compile_definitions(Unit_test_Interpolator_qpoly PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
)

# ############################TRANSFORMATION TEST##############################
add_executable(Unit_test_Transformation_qpoly
  TransformationTest.cpp
)

target_compile_definitions(Unit_test_Transformation_qpoly
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_test_Transformation_qpoly
  PRIVATE
  gtest_main
  gmock
  ImageTransformCommon
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
)
target_compile_definitions(Unit_test_QPolygonTransform_lib_qpoly PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
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
)

target_compile_definitions(Unit_test_ColorInterpolation PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
)
