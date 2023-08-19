set(INSTALL_PATH "${CMAKE_SOURCE_DIR}/../1.Install_location")
set(CMAKE_INSTALL_PREFIX "C:/Users/mplesniak/Desktop/1. Mentoring_QT_project/1.Install_location" CACHE PATH "" FORCE)

install(TARGETS BasicGUI
    RUNTIME DESTINATION "${INSTALL_PATH}"
    BUNDLE DESTINATION "${INSTALL_PATH}"
    LIBRARY DESTINATION "${INSTALL_PATH}"
)