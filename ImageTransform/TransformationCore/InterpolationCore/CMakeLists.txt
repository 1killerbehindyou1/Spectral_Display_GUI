set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(InterpolationCore STATIC
  InterpolatorBase.cpp)

target_compile_definitions(InterpolationCore
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(InterpolationCore
  PUBLIC
  ImageTransformCore
)

target_include_directories(InterpolationCore
  PUBLIC .
)
