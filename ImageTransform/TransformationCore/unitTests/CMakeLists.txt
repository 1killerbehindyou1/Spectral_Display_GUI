find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_COMMON})

# ############################INTERPOLATION CORE TEST##############################
add_executable(UnitTestInterpolatorCore
  UnitTestInterpolatorCore.cpp
)
target_compile_definitions(UnitTestInterpolatorCore
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestInterpolatorCore
  PUBLIC
  googletest_utils
  InterpolationCore
)
target_compile_definitions(UnitTestInterpolatorCore PRIVATE
  -DOUTPUT_IMG_PATH="${GUI_OUTPUT_GENERATED_IMG_PATH_TEST_QPOLY}"
  -DINPUT_IMG_PATH="${GUI_SAMPLE_IMAGES_PATH}/${GUI_TESTING_IMG_QPOLY}"
)

# ############################TRANSFORMATION CORE TEST##############################
add_executable(UnitTestTransformationCore
  UnitTestTransformationCore.cpp
)

target_compile_definitions(UnitTestTransformationCore
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestTransformationCore
  PRIVATE
  ImageTransformCore
  googletest_utils
)

add_test(NAME UnitTestTransformationCore COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UnitTestTransformationCore
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTestTransformationCore)