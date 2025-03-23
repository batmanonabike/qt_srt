cmake_minimum_required(VERSION 3.16)

project(RTMPViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Enable AUTOMOC
set(CMAKE_AUTORCC ON)  # Enable AUTORCC for resources
set(CMAKE_AUTOUIC ON)  # Enable AUTOUIC for UI files

# message(STATUS "PKG_CONFIG_PATH=${PKG_CONFIG_PATH}")
message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(PkgConfig REQUIRED)
qt_standard_project_setup()

# Check GStreamer version using pkg-config
# See ReadMe.md for more information:
# vckpk\vcpkg install gstreamer[plugins-bad] --recurse
# Previously: vcpkg\vcpkg install gstreamer
execute_process(
    COMMAND pkg-config --modversion gstreamer-1.0
    OUTPUT_VARIABLE GSTREAMER_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
if(NOT GSTREAMER_VERSION)
     message(FATAL_ERROR "GStreamer not found. Please install GStreamer.")
else()
    message(STATUS "Found GStreamer version ${GSTREAMER_VERSION}")
endif()

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

if(GSTREAMER_FOUND)
    message(STATUS "GStreamer found via pkg-config")
    message(STATUS "GSTREAMER_LIBRARIES=${GSTREAMER_LIBRARIES}")
    message(STATUS "GSTREAMER_LIBRARY_DIRS=${GSTREAMER_LIBRARY_DIRS}")
    message(STATUS "GSTREAMER_INCLUDE_DIRS=${GSTREAMER_INCLUDE_DIRS}")

    link_directories(${GSTREAMER_LIBRARY_DIRS})
else()
    message(WARNING "GStreamer not found via pkg-config")
endif()

qt_add_executable(RTMPViewer
    main.cpp
    VideoPlayer.cpp
    VideoPlayer.h
    qml.qrc
)

# qt_add_qml_module command is used to define a QML module, useful for reusable QML components or libraries
# Alternative to qt_add_executable with qml.qrc.
#
# qt_add_qml_module(RTMPViewer
#    URI RTMPViewer
#    VERSION 1.0
#    QML_FILES main.qml
#)

target_include_directories(RTMPViewer PRIVATE ${GSTREAMER_INCLUDE_DIRS})

# gstreamer-1.0.lib  
target_link_libraries(RTMPViewer PRIVATE Qt6::Quick ${GSTREAMER_LIBRARIES})

if(WIN32)
    # Find GStreamer bin directory
    pkg_get_variable(GSTREAMER_BIN_DIR gstreamer-1.0 exec_prefix)
    if(GSTREAMER_BIN_DIR)
        # Convert to native path format
        file(TO_NATIVE_PATH "${GSTREAMER_BIN_DIR}/bin" GSTREAMER_BIN_NATIVE)
        message(STATUS "GStreamer bin directory: ${GSTREAMER_BIN_NATIVE}")
        
        # Configure the app to find DLLs at runtime
        set_target_properties(RTMPViewer PROPERTIES
            VS_DEBUGGER_ENVIRONMENT "PATH=${GSTREAMER_BIN_NATIVE};%PATH%")
            
        # Optional: Copy DLLs to output directory post-build
        add_custom_command(TARGET RTMPViewer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${GSTREAMER_BIN_DIR}/bin" "$<TARGET_FILE_DIR:RTMPViewer>")
    endif()
endif()
