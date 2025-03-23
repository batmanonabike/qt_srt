cmake_minimum_required(VERSION 3.16)

project(MockCameraApp2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include(qt.cmake)

find_package(Qt6 COMPONENTS Core Quick Multimedia REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    MockCamera.cpp
    MockCamera.h
    CameraController.cpp
    CameraController.h
    qml.qrc
)

qt_add_executable(MockCameraApp2 ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/QtSrtMainLib/include)

target_link_libraries(MockCameraApp2 PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
    QtSrtMainLib
)

