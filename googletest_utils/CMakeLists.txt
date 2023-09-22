find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(googletest_utils
    src/mainTests.cpp
    includes/CommonTestsImpl.hpp
)
target_compile_definitions(googletest_utils
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(googletest_utils
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    PUBLIC
    gtest
    gmock
)

target_include_directories(googletest_utils PUBLIC
    includes)