find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(UnitTestAppCore
  UnitTestAppCore.cpp
  ${CMAKE_SOURCE_DIR}/main/app/include/FileManager.hpp
  ${CMAKE_SOURCE_DIR}/main/app/include/TransformEngine.hpp
  ${CMAKE_SOURCE_DIR}/main/app/source/FileManager.cpp
  ${CMAKE_SOURCE_DIR}/main/app/source/TransformEngine.cpp
)

target_compile_definitions(UnitTestAppCore
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestAppCore
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  googletest_utils
  QPolygonTransform
)

target_include_directories(UnitTestAppCore
  PRIVATE
  ${CMAKE_SOURCE_DIR}/main/app/include
)

add_test(NAME UnitTestAppCore
  COMMAND $<TARGET_FILE:UnitTestAppCore>
)

set_target_properties(UnitTestAppCore PROPERTIES
  AUTOMOC ON
)
