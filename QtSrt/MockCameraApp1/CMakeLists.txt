cmake_minimum_required(VERSION 3.16)
project(MockCameraApp1 LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} 
    COMPONENTS
        Quick
        Multimedia
)
qt_standard_project_setup()

# Print Qt Quick location, include directories, and libraries AFTER calling qt_standard_project_setup()
get_target_property(QtQuick_LOCATION Qt::Quick LOCATION)
message(STATUS "Qt::Quick LOCATION: ${QtQuick_LOCATION}")

get_target_property(QtQuick_INCLUDE_DIRS Qt::Quick INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "Qt::Quick INCLUDE_DIRS: ${QtQuick_INCLUDE_DIRS}")

get_target_property(QtQuick_LIBRARIES Qt::Quick INTERFACE_LINK_LIBRARIES)
message(STATUS "Qt::Quick LIBRARIES: ${QtQuick_LIBRARIES}")

set(PROJECT_SOURCES main.cpp)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

if(QT_VERSION VERSION_GREATER_EQUAL 6.2)
    qt_add_qml_module(${PROJECT_NAME}
        URI MockCameraApp1
        VERSION 1.0
        RESOURCE_PREFIX "/qt/qml/"
        QML_FILES
            main.qml
    )
endif()

qt_add_resources(${PROJECT_NAME} "resources"
    PREFIX "/"
    FILES main.qml
)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Quick
        Qt::Multimedia
)

# Add MESSY AF includes directory for the SRT library, this feels all wrong.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/srt/srtcore)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/srt/common)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/srt) # version.h - horrid

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/QtSrtMainLib/include)

# target_link_libraries(${PROJECT_NAME} PRIVATE srt)
target_link_libraries(${PROJECT_NAME} PRIVATE srt_static)
target_link_libraries(${PROJECT_NAME} PRIVATE QtSrtMainLib)

if(Qt6_FOUND)
    qt_import_qml_plugins(${PROJECT_NAME})
endif()

# Copy Qt DLLs to the output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_PREFIX_PATH}/bin/Qt6Multimedia.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
