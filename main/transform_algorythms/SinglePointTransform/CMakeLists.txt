set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(SinglePointTransform STATIC
  InterpolatorSingle.cpp
)

target_compile_definitions(SinglePointTransform
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(SinglePointTransform
  PUBLIC
  InterpolationCore
)
target_include_directories(SinglePointTransform PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
