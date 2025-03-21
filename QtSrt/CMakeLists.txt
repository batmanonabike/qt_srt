cmake_minimum_required(VERSION 3.16)
project(YourProjectName LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# NOTE THESE MY NEED TO BE CHANGED TO THE PATH WHERE YOU INSTALLED QT... 
# It's not picking it up from the environment variable for some reason, its being overriden.
set(QTDIR "C:/Qt/6.8.2/msvc2022_64")
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")

# Add subdirectories
add_subdirectory(SimulateCamera)
