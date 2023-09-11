set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(SinglePointTransform STATIC
  src/InterpolatorSingle.cpp)

target_compile_definitions(SinglePointTransform
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(SinglePointTransform
  PUBLIC
  BaseInterpolation
)
target_include_directories(SinglePointTransform PUBLIC
  src
)

add_subdirectory(unit_tests)