cmake_minimum_required(VERSION 3.16)
project(QtSrt LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/common.cmake)

# Add the SRT project as a subdirectory and disable encryption
set(ENABLE_ENCRYPTION ON CACHE BOOL "Encryption in SRT")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build SRT as a static library") 
set(OPENSSL_USE_STATIC_LIBS ON CACHE BOOL "Link OpenSSL libraries statically.")

add_subdirectory("srt")
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/srt" 
    PROPERTY CMAKE_CACHE_ARGS 
    "-DENABLE_ENCRYPTION:BOOL=${ENABLE_ENCRYPTION}"
    "-DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}"
    "-DOPENSSL_USE_STATIC_LIBS:BOOL=${OPENSSL_USE_STATIC_LIBS}"
)

add_subdirectory(QtSrtMainLib)
add_subdirectory(MockCameraApp1)
add_subdirectory(MockCameraApp2)
add_subdirectory(RTMPViewer)
