cmake_minimum_required(VERSION 3.16)
project(FFmpeg LANGUAGES C)

include(ExternalProject)

# Set the installation directory for FFmpeg
set(FFMPEG_INSTALL_DIR ${CMAKE_BINARY_DIR}/ffmpeg/install)

# Path to the FFmpeg submodule
set(FFMPEG_SOURCE_DIR ${EXTERNAL_PROJECT_DIR}/ffmpeg-submodule)

# Add libx264 as an external project (using existing submodule)
message(STATUS "EXTERNAL_PROJECT_DIR=${EXTERNAL_PROJECT_DIR}")
message(STATUS "ENV{PATH}=$ENV{PATH}")

ExternalProject_Add(
    x264
    SOURCE_DIR ${EXTERNAL_PROJECT_DIR}/x264
    PREFIX ${CMAKE_BINARY_DIR}/x264
    CONFIGURE_COMMAND ${CONFIGURE_COMMAND}
    BUILD_COMMAND ${BUILD_COMMAND}
    INSTALL_COMMAND ${INSTALL_COMMAND}
    BUILD_IN_SOURCE 1
)


#[[
# Add libx265 as an external project (using existing submodule)
ExternalProject_Add(
    x265
    SOURCE_DIR ${EXTERNAL_PROJECT_DIR}/x265
    PREFIX ${CMAKE_BINARY_DIR}/x265
    CONFIGURE_COMMAND cmake -DCMAKE_INSTALL_PREFIX=${FFMPEG_INSTALL_DIR} .
    BUILD_COMMAND make -j4
    INSTALL_COMMAND make install
    BUILD_IN_SOURCE 1
)

# Add libvpx as an external project (using existing submodule)
ExternalProject_Add(
    vpx
    SOURCE_DIR ${EXTERNAL_PROJECT_DIR}/libvpx
    PREFIX ${CMAKE_BINARY_DIR}/vpx
    CONFIGURE_COMMAND ./configure --prefix=${FFMPEG_INSTALL_DIR} --enable-shared --disable-static
    BUILD_COMMAND make -j4
    INSTALL_COMMAND make install
    BUILD_IN_SOURCE 1
)

# Add FFmpeg as an external project (using existing submodule)
ExternalProject_Add(
    ffmpeg
    SOURCE_DIR ${FFMPEG_SOURCE_DIR}
    PREFIX ${CMAKE_BINARY_DIR}/ffmpeg
    CONFIGURE_COMMAND ./configure --prefix=${FFMPEG_INSTALL_DIR} --enable-gpl --enable-libx264 --enable-libx265 --enable-libvpx --enable-shared --disable-static
    BUILD_COMMAND cmake --build . --config Release
    INSTALL_COMMAND cmake --build . --target install
    BUILD_IN_SOURCE 1
    DEPENDS x264 x265 vpx
)

# Include FFmpeg headers and libraries
include_directories(${FFMPEG_INSTALL_DIR}/include)
link_directories(${FFMPEG_INSTALL_DIR}/lib)

# Create a dummy target to ensure FFmpeg is built before other targets
add_custom_target(ffmpeg_dummy ALL DEPENDS ffmpeg)

set(FFMPEG_INCLUDE_DIR ${FFMPEG_INSTALL_DIR}/include PARENT_SCOPE)
set(FFMPEG_LIBRARY_DIR ${FFMPEG_INSTALL_DIR}/lib PARENT_SCOPE)

]]
