find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

# ///////////////////////////////INTERPOLATOR TEST////////////////////////////////
preparing_QPolygonTest_tests(QPolygon_test)

add_executable(InterpolatorTest_qpoly
  InterpolatorTest.cpp
)

target_include_directories(InterpolatorTest_qpoly PUBLIC
  ${QPOLYGON_INCLUDE_DIR}
  ${COMMON_HEADERS}
)

target_link_libraries(InterpolatorTest_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

target_compile_definitions(InterpolatorTest_qpoly PRIVATE
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

# ############################TRANSFORMATION TEST##############################
add_executable(TransformationTest_qpoly
  TransformationTest.cpp
)

target_include_directories(TransformationTest_qpoly PUBLIC
  ${QPOLYGON_INCLUDE_DIR}
  ${COMMON_HEADERS}
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

target_include_directories(QPolygonTransform_libTest_qpoly PUBLIC
  ${QPOLYGON_INCLUDE_DIR}
  ${COMMON_HEADERS}
)

target_link_libraries(QPolygonTransform_libTest_qpoly
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)
target_compile_definitions(QPolygonTransform_libTest_qpoly PRIVATE
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

# ############################COLORINTERPOLTEST TEST##############################
add_executable(ColorInterpolationTest
  ColorInterpolationTest.cpp
)

target_include_directories(ColorInterpolationTest PUBLIC
  ${QPOLYGON_INCLUDE_DIR}
  ${COMMON_HEADERS}
)

target_link_libraries(ColorInterpolationTest
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

target_compile_definitions(ColorInterpolationTest PRIVATE
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)
