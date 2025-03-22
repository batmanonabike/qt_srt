cmake_minimum_required(VERSION 3.16)

project(RTMPViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

qt_add_executable(RTMPViewer
    main.cpp
    VideoPlayer.cpp
    VideoPlayer.h
)

qt_add_qml_module(RTMPViewer
    URI RTMPViewer
    VERSION 1.0
    QML_FILES main.qml
)

target_include_directories(RTMPViewer PRIVATE ${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(RTMPViewer PRIVATE Qt6::Quick ${GSTREAMER_LIBRARIES})
