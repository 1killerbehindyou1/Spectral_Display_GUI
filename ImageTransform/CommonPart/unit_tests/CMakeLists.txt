find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_CMAKE_RUNTIME_OUTPUT_DIR_TEST_COMMON})

add_executable(Unit_Test_CommonPart_lib
  Unit_Test_CommonPart_lib.cpp
)

target_compile_definitions(Unit_Test_CommonPart_lib
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(Unit_Test_CommonPart_lib
  PRIVATE
  googletest_utils
  ImageTransformCommon
)
target_include_directories(Unit_Test_CommonPart_lib PRIVATE ../src)