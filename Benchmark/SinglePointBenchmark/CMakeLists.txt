set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

add_executable(SinglePointBenchmark
    SinglePointTask.cpp
)

target_compile_definitions(SinglePointBenchmark
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(SinglePointBenchmark
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    SinglePointTransform
    LibraryBenchmark
    ImageTransformCommon
)
