find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

add_executable(InterpolatorTest
  InterpolatorTest.cpp
)

target_include_directories(InterpolatorTest
  PUBLIC ../src
)

target_compile_definitions(InterpolatorTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(InterpolatorTest
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)

add_executable(TransformationTest
  TransformationTest.cpp
)

target_include_directories(TransformationTest
  PUBLIC ../src
)

target_compile_definitions(TransformationTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(TransformationTest
  PRIVATE
  gtest_main
  gmock
  QPolygonTransform

  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
)