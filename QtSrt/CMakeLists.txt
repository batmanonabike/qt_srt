cmake_minimum_required(VERSION 3.16)
project(QtSrt LANGUAGES CXX)

# See ReadMe.md for more information

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(/EHsc) # Add the /EHsc flag for exception handling

# NOTE THESE MY NEED TO BE CHANGED TO THE PATH WHERE YOU INSTALLED QT... 
# It's not picking it up from the environment variable for some reason, its being overriden.
set(QTDIR "C:/Qt/6.8.2/msvc2022_64")
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")

set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

if(WIN32)
     set(ENV{PKG_CONFIG_PATH} "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/pkgconfig;$ENV{PKG_CONFIG_PATH}")
else()
    set(ENV{PKG_CONFIG_PATH} "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

# set(PKG_CONFIG_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/pkgconfig")
message(STATUS "PKG_CONFIG_PATH=${PKG_CONFIG_PATH}")
message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

# Set OpenSSL for Windows (this will need adjusting for Android/cross platform).
set(OPENSSL_LIBRARIES "C:/Program Files/OpenSSL/lib")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL/include")
# set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../openssl/include")
# set(OPENSSL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../openssl/lib")
message(STATUS "OPENSSL_LIBRARIES=${OPENSSL_LIBRARIES}")
message(STATUS "OPENSSL_INCLUDE_DIR=${OPENSSL_INCLUDE_DIR}")

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
add_subdirectory(RTMPViewer)
add_subdirectory(SimulateCamera)

# Link SRT library to your project (example)
# target_link_libraries(${PROJECT_NAME} PRIVATE srt) 