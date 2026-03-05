find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(UnitTestRenderEngine
  UnitTestRenderEngine.cpp
  ${CMAKE_SOURCE_DIR}/main/app/include/RenderEngine.hpp
  ${CMAKE_SOURCE_DIR}/main/app/source/RenderEngine.cpp
)

target_compile_definitions(UnitTestRenderEngine
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestRenderEngine
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Quick
  googletest_utils
  QPolygonTransform
)

target_include_directories(UnitTestRenderEngine
  PRIVATE
  ${CMAKE_SOURCE_DIR}/main/app/include
)

set_target_properties(UnitTestRenderEngine PROPERTIES
  AUTOMOC ON
)

add_test(NAME UnitTestRenderEngine
  COMMAND $<TARGET_FILE:UnitTestRenderEngine>
)
