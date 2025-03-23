cmake_minimum_required(VERSION 3.16)
project(MockCameraApp1 LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "QTDIR=${QTDIR}!")
message(STATUS "CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}!")

# Check for the existence of Qt6Multimedia.lib
if(NOT EXISTS "${CMAKE_PREFIX_PATH}/lib/Qt6Multimedia.lib")
    message(FATAL_ERROR "Qt6Multimedia.lib not found in ${CMAKE_PREFIX_PATH}/lib")
else()
    message(STATUS "Qt6Multimedia.lib found in ${CMAKE_PREFIX_PATH}/lib")
endif()

# Check for the existence of Qt6Multimedia.dll
if(NOT EXISTS "${CMAKE_PREFIX_PATH}/bin/Qt6Multimedia.dll")
    message(FATAL_ERROR "Qt6Multimedia.dll not found in ${CMAKE_PREFIX_PATH}/bin")
else()
    message(STATUS "Qt6Multimedia.dll found in ${CMAKE_PREFIX_PATH}/bin")
endif()

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

set(PROJECT_SOURCES
    main.cpp
)

if(QT_VERSION VERSION_LESS 5.15)
    qt5_add_resources(PROJECT_SOURCES qml.qrc)
elseif(QT_VERSION VERSION_LESS 6.2)
    qt_add_resources(PROJECT_SOURCES qml.qrc)
endif()

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

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Quick
        Qt::Multimedia
)

# Add MESSY AF includes directory for the SRT library, this feels all wrong.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/srt/srtcore)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/srt/common)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/srt) # version.h - horrid

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/QtSrtMainLib)

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
