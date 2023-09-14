set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(BaseInterpolation STATIC
  InterpolatorBase.cpp)

target_compile_definitions(BaseInterpolation
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(BaseInterpolation
  PUBLIC
  ImageTransformCommon
)

target_include_directories(BaseInterpolation
  PUBLIC .
)
