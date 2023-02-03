find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

add_executable(BackendTests
    InterpolatorTest.cpp
)

target_compile_definitions(BackendTests
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(BackendTests
    PRIVATE
        gtest_main
        gmock
        Interpolator

        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
)
