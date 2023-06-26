find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestSinglePointTransformLibrary)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../../Pictures/BITMAPA.png
  DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/)

set(INPUT_IMG_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/Pictures/BITMAPA.png)
set(OUTPUT_IMG_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GeneratedPicture)

add_custom_target(build-time-make-directory ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_library)

# #############################LIBRARY TEST#################################
add_executable(SinglePointTransform_libTest
  SinglePointTransform_libTest.cpp
)

target_compile_definitions(SinglePointTransform_libTest PRIVATE
  -DBINARY_BUILD_PATH="${CMAKE_BINARY_DIR}/bin"
  -DOUTPUT_IMG_PATH="${OUTPUT_IMG_PATH}"
  -DINPUT_IMG_PATH="${INPUT_IMG_PATH}"
)

target_include_directories(SinglePointTransform_libTest
  PUBLIC ../include
)

target_compile_definitions(SinglePointTransform_libTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(SinglePointTransform_libTest
  PRIVATE
  gtest_main
  gmock
  SinglePointTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)