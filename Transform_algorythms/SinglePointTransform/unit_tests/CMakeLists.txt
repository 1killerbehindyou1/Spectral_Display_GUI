find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

# #############################LIBRARY TEST#################################
preparing_singlePoint_tests(SinglePoint_test)

add_executable(SinglePointTransform_libTest
  SinglePointTransform_libTest.cpp
)

target_compile_definitions(SinglePointTransform_libTest PRIVATE
  $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
  -DBINARY_BUILD_PATH="${CMAKE_BINARY_DIR}/bin"
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

target_include_directories(SinglePointTransform_libTest PUBLIC
  ${SINGLE_POINT_INCLUDE_DIR}
  ${COMMON_HEADERS}
)

target_link_libraries(SinglePointTransform_libTest
  PRIVATE
  gtest_main
  gmock
  SinglePointTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)