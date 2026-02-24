find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(UnitTestRenderSelector
  UnitTestRenderSelector.cpp
  ${CMAKE_SOURCE_DIR}/main/app/include/RenderSelector.hpp
  ${CMAKE_SOURCE_DIR}/main/app/source/RenderSelector.cpp
)

target_compile_definitions(UnitTestRenderSelector
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestRenderSelector
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Quick
  googletest_utils
)

target_include_directories(UnitTestRenderSelector
  PRIVATE
  ${CMAKE_SOURCE_DIR}/main/app/include
)

set_target_properties(UnitTestRenderSelector PROPERTIES
  AUTOMOC ON
)

add_test(NAME UnitTestRenderSelector
  COMMAND $<TARGET_FILE:UnitTestRenderSelector>
)
