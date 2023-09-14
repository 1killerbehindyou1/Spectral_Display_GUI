set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_QPOLY})

add_custom_target(build-time-make-directory-qpoly ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_polygon_ruler_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_bounding_rect_print
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_polygon_contains_point
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_library
  COMMAND ${CMAKE_COMMAND} -E make_directory ${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}/test_color)

# ///////////////////////////////INTERPOLATOR TEST////////////////////////////////
add_executable(UnitTestInterpolatorQPolygon
  UnitTestColorInterpolation.cpp
)
target_compile_definitions(UnitTestInterpolatorQPolygon
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestInterpolatorQPolygon
  PUBLIC
  googletest_utils
  QPolygonTransform
)
target_compile_definitions(UnitTestInterpolatorQPolygon PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
)

# ############################TRANSFORMATION TEST##############################
add_executable(UnitTestTransformationQPolygon
  UnitTestTransformation.cpp
)

target_compile_definitions(UnitTestTransformationQPolygon
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestTransformationQPolygon
  PRIVATE
  googletest_utils
  ImageTransformCommon
)

# #############################LIBRARY TEST#################################
add_executable(UnitTestQPolygonTransformLib
  UnitTestQPolygonTransform.cpp
)

target_compile_definitions(UnitTestQPolygonTransformLib
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestQPolygonTransformLib
  PRIVATE
  googletest_utils
  QPolygonTransform
)
target_compile_definitions(UnitTestQPolygonTransformLib PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
)

# ############################COLORINTERPOLTEST TEST##############################
add_executable(UnitTestColorInterpolation
  UnitTestColorInterpolation.cpp
)

target_compile_definitions(UnitTestColorInterpolation
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestColorInterpolation
  PRIVATE
  googletest_utils
  QPolygonTransform
)

target_compile_definitions(UnitTestColorInterpolation PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
)
