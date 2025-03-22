cmake_minimum_required(VERSION 3.16)

project(MockCameraApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Quick Multimedia REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mockcamera.cpp
    mockcamera.h
    cameracontroller.cpp
    cameracontroller.h
    qml.qrc
)

qt_add_executable(MockCameraApp
    ${PROJECT_SOURCES}
)

target_link_libraries(MockCameraApp PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
)
