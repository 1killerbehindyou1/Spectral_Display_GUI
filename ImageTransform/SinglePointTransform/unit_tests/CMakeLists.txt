find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_SINGLE})

add_custom_target(make_directory_for_singlePointTest ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_library)

add_executable(UnitTestSinglePointTransform
  UnitTestSinglePointTransform.cpp
)

target_compile_definitions(UnitTestSinglePointTransform PRIVATE
  -DBINARY_BUILD_PATH="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_SINGLE}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_SINGLE}"
)

target_compile_definitions(UnitTestSinglePointTransform
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestSinglePointTransform
  PRIVATE
  googletest_utils
  SinglePointTransform
)

add_test(NAME UnitTestSinglePointTransform
  COMMAND $<TARGET_FILE:UnitTestSinglePointTransform>
)