project(SpectralDisplay VERSION 0.1 DESCRIPTION "General project SPRCTRAL DISPLAY" LANGUAGES CXX)

if(BUILD_DOCUMENTATION)
    find_package(Doxygen QUIET)

    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR
            "BUILD_DOCUMENTATION=ON requires Doxygen, but the 'doxygen' executable was not found. "
            "Install it first, for example on Ubuntu/Debian: sudo apt install doxygen"
        )
    endif()

    set(DOXYGEN_OUTPUT_ROOT "${CMAKE_SOURCE_DIR}/build")
    set(DOXYGEN_HTML_SUBDIR "doxygen_html")

    configure_file(
        ${CMAKE_SOURCE_DIR}/documentation/Doxyfile.in
        ${CMAKE_BINARY_DIR}/Doxyfile
        @ONLY
    )

    file(READ "${CMAKE_BINARY_DIR}/Doxyfile" DOXYFILE_CONTENT)
    string(REGEX REPLACE "OUTPUT_DIRECTORY[ \t]*=[^\n]*"
        "OUTPUT_DIRECTORY = ${DOXYGEN_OUTPUT_ROOT}" DOXYFILE_CONTENT "${DOXYFILE_CONTENT}")
    string(REGEX REPLACE "HTML_OUTPUT[ \t]*=[^\n]*"
        "HTML_OUTPUT = ${DOXYGEN_HTML_SUBDIR}" DOXYFILE_CONTENT "${DOXYFILE_CONTENT}")
    file(WRITE "${CMAKE_BINARY_DIR}/Doxyfile" "${DOXYFILE_CONTENT}")

    add_custom_target(DoxygenDoc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

endif()

install(DIRECTORY "${CMAKE_SOURCE_DIR}/build/doxygen_html/"
    DESTINATION doxygen_html
    OPTIONAL
)