cmake_minimum_required(VERSION 3.16)

project(MockCameraApp2 LANGUAGES CXX)

set(PROJECT_SOURCES main.cpp qml.qrc)

find_package(Qt6 COMPONENTS Core Quick Multimedia REQUIRED)
qt_standard_project_setup()

qt_add_executable(MockCameraApp2 ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE QtSrtMainLib)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/QtSrtMainLib/include)


