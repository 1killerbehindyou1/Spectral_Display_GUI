find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_COMMON})

add_executable(UnitTestCommonPartLib
  UnitTestCommonPart.cpp
)

target_compile_definitions(UnitTestCommonPartLib
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestCommonPartLib
  PRIVATE
  googletest_utils
  ImageTransformCommon
)
target_include_directories(UnitTestCommonPartLib PRIVATE ../src)