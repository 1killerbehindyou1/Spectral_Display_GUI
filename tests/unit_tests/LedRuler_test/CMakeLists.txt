find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(UnitTestLedRuler
  UnitTestLedRuler.cpp
  ${CMAKE_SOURCE_DIR}/main/app/include/LedRuler.hpp
  ${CMAKE_SOURCE_DIR}/main/app/source/LedRuler.cpp
)

target_compile_definitions(UnitTestLedRuler
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(UnitTestLedRuler
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Quick
  googletest_utils
  QPolygonTransform
)

target_include_directories(UnitTestLedRuler
  PRIVATE
  ${CMAKE_SOURCE_DIR}/main/app/include
)

set_target_properties(UnitTestLedRuler PROPERTIES
  AUTOMOC ON
)

add_test(NAME UnitTestLedRuler
  COMMAND $<TARGET_FILE:UnitTestLedRuler>
)
