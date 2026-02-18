
function(preparing_benchmark arg0)
    add_custom_target(make-directory-benchmark ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin/benchmark_test)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/benchmark_test)

    file(COPY ${IMAGES_DIR}/BITMAPA.png
        DESTINATION ${CMAKE_BINARY_DIR}/bin/benchmark_test/pictures/)
endfunction()

function(preparing_singlePoint_tests arg0)
    add_custom_target(make-directory-tests ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_library)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/UnitTests/TestSinglePointTransformLibrary)

    file(COPY ${IMAGES_DIR}/BITMAPA.png
        DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/pictures/)
endfunction()

function(preparing_QPolygonTest_tests arg0)
    set(OUTPUT_IMG_PATH ${CMAKE_BINARY_DIR}/bin/UnitTests/TestSinglePointTransformLibrary/GeneratedPicture)

    add_custom_target(build-time-make-directory-qpoly ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_polygon_ruler_print
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_bounding_rect_print
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_polygon_contains_point
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_library
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_IMG_PATH}/test_color)

    file(COPY ${IMAGES_DIR}/BITMAPA.png
        DESTINATION ${CMAKE_BINARY_DIR}/bin/UnitTests/pictures/)
endfunction()