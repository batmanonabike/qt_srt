# See ReadMe.md for more information

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# See: qt_standard_project_setup() 
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# Add common compile options
add_compile_options(/EHsc)

# Set common paths (adjust these paths as needed)
set(QTDIR "C:/Qt/6.8.2/msvc2022_64")
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/msvc2022_64")

# THIS WILL NEED TO CHANGE...
# set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
set(VCPKG_ROOT "C:/source/repos/qt_srt_29/QtSrt/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# Set OpenSSL for Windows (this will need adjusting for Android/cross platform).
set(OPENSSL_LIBRARIES "C:/Program Files/OpenSSL/lib")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/OpenSSL/include")
# set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../openssl/include")
# set(OPENSSL_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../openssl/lib")

# Set environment variables for pkg-config (this will need adjusting for Android/cross platform).
if(WIN32)
    set(ENV{PKG_CONFIG_PATH} "${VCPKG_ROOT}/installed/x64-windows/lib/pkgconfig;$ENV{PKG_CONFIG_PATH}")
else()
    set(ENV{PKG_CONFIG_PATH} "${VCPKG_ROOT}/installed/x64-windows/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

find_program(BASH_EXECUTABLE bash HINTS "C:/msys64/usr/bin")

if(NOT BASH_EXECUTABLE)
    message(FATAL_ERROR "Bash executable not found. Please install MSYS2 or Git for Windows.")
endif()

# set(ENV{PATH} "C:/msys64/usr/bin;$ENV{PATH}")
# set(ENV{EXTERNAL_PROJECT_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(EXTERNAL_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# Tried to add to SYSTEM envirnonment variable, but it didn't work.
# C:\msys64\usr\bin
# C:\msys64\mingw64\bin
# pacman -S nasm
# pacman -S mingw-w64-x86_64-gcc

# Determine platform-specific command execution
set(CONFIGURE_COMMAND ${BASH_EXECUTABLE} -c "./configure --prefix=${FFMPEG_INSTALL_DIR} --enable-shared --disable-static")
set(BUILD_COMMAND ${BASH_EXECUTABLE} -c "make -j4")
set(INSTALL_COMMAND ${BASH_EXECUTABLE} -c "make install")

# if(WIN32)
#     set(CONFIGURE_COMMAND ${BASH_EXECUTABLE} -c "export PATH=/usr/bin:\$PATH && ${EXTERNAL_PROJECT_DIR}/x264/configure --prefix=${FFMPEG_INSTALL_DIR} --enable-shared --disable-static")
#     set(BUILD_COMMAND ${BASH_EXECUTABLE} -c "export PATH=/usr/bin:\$PATH && make -j4")
#     set(INSTALL_COMMAND ${BASH_EXECUTABLE} -c "export PATH=/usr/bin:\$PATH && make install")
# else()
#     set(CONFIGURE_COMMAND ./configure --prefix=${FFMPEG_INSTALL_DIR} --enable-shared --disable-static)
#     set(BUILD_COMMAND make -j4)
#     set(INSTALL_COMMAND make install)
# endif()

# set(CONFIGURE_COMMAND bash.exe ./configure --prefix=${FFMPEG_INSTALL_DIR} --enable-shared --disable-static)
# set(BUILD_COMMAND make -j4)
# set(INSTALL_COMMAND make install)

# Print status messages
message(STATUS "PKG_CONFIG_PATH=${PKG_CONFIG_PATH}")
message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "OPENSSL_LIBRARIES=${OPENSSL_LIBRARIES}")
message(STATUS "OPENSSL_INCLUDE_DIR=${OPENSSL_INCLUDE_DIR}")
message(STATUS "EXTERNAL_PROJECT_DIR=${EXTERNAL_PROJECT_DIR}")
message(STATUS "ENV{PATH}=$ENV{PATH}")
