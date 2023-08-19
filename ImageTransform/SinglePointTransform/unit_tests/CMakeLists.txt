find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestSinglePointTransformLibrary)

# file(COPY ${IMAGE_TESTED_SRC_PATH}
# DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/)

# set(INPUT_IMG_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/BITMAPA.png)
# set(OUTPUT_IMG_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GeneratedPicture)

# add_custom_target(make_directory_for_singlePointTest ALL
# COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_library)

# #############################LIBRARY TEST#################################
add_executable(Unit_Test_SinglePointTransform_lib
  Unit_Test_SinglePointTransform_lib.cpp
)

target_compile_definitions(Unit_Test_SinglePointTransform_lib PRIVATE
  -DBINARY_BUILD_PATH="${CMAKE_BINARY_DIR}/bin"
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

target_compile_definitions(Unit_Test_SinglePointTransform_lib
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_Test_SinglePointTransform_lib
  PUBLIC
  gtest_main
  gmock

  SinglePointTransform
  ImageTransformCommon
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)