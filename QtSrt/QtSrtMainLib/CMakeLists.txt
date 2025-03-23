cmake_minimum_required(VERSION 3.16)
project(QtSrtMainLib LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Quick Multimedia REQUIRED)
qt_standard_project_setup()

set(PROJECT_SOURCES
    "src/MockCamera.cpp"
    "src/QtSrtMainLib.cpp"
    "src/CameraController.cpp"
    "include/QtSrtMainLib/MockCamera.h"
    "include/QtSrtMainLib/QtSrtMainLib.h"
    "include/QtSrtMainLib/CameraController.h"
    "include/QtSrtMainLib/QtSrtMainLibGlobal.h"
)

set(PROJECT_LIBS
    "Qt6::Core"
    "Qt6::Quick"
    "Qt6::Multimedia"
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIBS})
target_compile_definitions(${PROJECT_NAME} PRIVATE QTSRTMAINLIB_LIB)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
