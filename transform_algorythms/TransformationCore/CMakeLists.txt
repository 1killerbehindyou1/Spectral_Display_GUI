set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(TransformationCore)
add_subdirectory(InterpolationCore)

if(BUILD_UT)
    add_subdirectory(unitTests)
endif()