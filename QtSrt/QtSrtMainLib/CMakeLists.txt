cmake_minimum_required(VERSION 3.16)
project(QtSrtMainLib LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    qtsrtmainlib_global.h
    QtSrtMainLib.h
    QtSrtMainLib.cpp
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        QTSRTMAINLIB_LIB
)

