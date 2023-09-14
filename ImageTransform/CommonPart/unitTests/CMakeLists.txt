find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_COMMON})

add_executable(UnitTestCommonPart
  UnitTestCommonPart.cpp
)

target_compile_definitions(UnitTestCommonPart
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestCommonPart
  PRIVATE
  googletest_utils
  ImageTransformCommon
)

add_test(NAME UnitTestCommonPart COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UnitTestCommonPart.exe
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTestCommonPart.exe)