find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(UnitTestOutPreview
  UnitTestOutPreview.cpp
  ${CMAKE_SOURCE_DIR}/main/app/include/OutputPreview.hpp
  ${CMAKE_SOURCE_DIR}/main/app/source/OutputPreview.cpp
)

target_compile_definitions(UnitTestOutPreview
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestOutPreview
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Quick
  googletest_utils
)

target_include_directories(UnitTestOutPreview
  PRIVATE
  ${CMAKE_SOURCE_DIR}/main/app/include
)

set_target_properties(UnitTestOutPreview PROPERTIES
  AUTOMOC ON
)

add_test(NAME UnitTestOutPreview
  COMMAND $<TARGET_FILE:UnitTestOutPreview>
)
