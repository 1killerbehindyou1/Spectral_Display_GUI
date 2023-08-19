set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Benchmark)

find_package(QT NAMES Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_library(LibraryBenchmark STATIC
    main.cpp
    MeasurementTools.cpp
)
target_include_directories(LibraryBenchmark PUBLIC public)

target_compile_definitions(LibraryBenchmark
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(LibraryBenchmark
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
)
