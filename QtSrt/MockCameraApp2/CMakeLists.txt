cmake_minimum_required(VERSION 3.16)

project(MockCameraApp2 LANGUAGES CXX)

include(qt.cmake)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick Multimedia REQUIRED)

set(PROJECT_SOURCES main.cpp qml.qrc)

qt_add_executable(MockCameraApp2 ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE QtSrtMainLib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/QtSrtMainLib/include)


