cmake_minimum_required(VERSION 3.16)
project(QtSrt LANGUAGES CXX)

# Add the /EHsc flag for exception handling
add_compile_options(/EHsc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# NOTE THESE MY NEED TO BE CHANGED TO THE PATH WHERE YOU INSTALLED QT... 
# It's not picking it up from the environment variable for some reason, its being overriden.
set(QTDIR "C:/Qt/6.8.2/msvc2022_64")
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")

# Add subdirectories
add_subdirectory(SimulateCamera)

# Set OpenSSL for Windows (this will need adjusting for Android/cross platform).
set(OPENSSL_LIBRARIES "C:/Program Files/OpenSSL/lib")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL/include")
# set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../openssl/include")
# set(OPENSSL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../openssl/lib")
message(STATUS "OPENSSL_LIBRARIES=${OPENSSL_LIBRARIES}")
message(STATUS "OPENSSL_INCLUDE_DIR=${OPENSSL_INCLUDE_DIR}")

# Add the SRT project as a subdirectory and disable encryption
set(ENABLE_ENCRYPTION OFF CACHE BOOL "Disable encryption in SRT")
add_subdirectory("../srt" "${CMAKE_BINARY_DIR}/srt_build")

set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../srt" 
    PROPERTY CMAKE_CACHE_ARGS 
    "-DENABLE_ENCRYPTION:BOOL=${ENABLE_ENCRYPTION}"
)

# Link SRT library to your project (example)
# target_link_libraries(${PROJECT_NAME} PRIVATE srt)
