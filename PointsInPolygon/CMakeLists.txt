

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_VERSION_MAJOR 5)

set(VAR1 2)


find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick QuickControls2 Gui )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Gui)

set(PROJECT_SOURCES
        Main.cpp
        QMLSources/qml.qrc
        Polygon.cpp
        Polygon.h
)


function(multi_scopes RESULT_VARIABLE)

    # here set(PARENT_SCOPE) is not usable because it will not set the
    # variable in the caller scope but in the parent scope of the block()
    set(${RESULT_VARIABLE} "new-value")
    message("MY_VAR is equal: " ${RESULT_VARIABLE})
    #return(PROPAGATE ${RESULT_VARIABLE})
  
endfunction()


set(MY_VAR "initial-value")
multi_scopes(MY_VAR)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PointsInPolygon
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BasicGUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PointsInPolygon SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PointsInPolygon
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(PointsInPolygon
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(PointsInPolygon
  PRIVATE 
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::Quick 
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::QuickControls2
)
  
set_target_properties(PointsInPolygon PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(PointsInPolygon)
    qt_finalize_executable(PointsInPolygon)
endif()

