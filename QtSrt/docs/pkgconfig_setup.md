# Installing and Using pkg-config with CMake

## Overview
pkg-config is a helper tool used to compile applications and libraries, providing a unified interface for querying installed libraries and their dependencies.

## Installation Instructions

### Windows

#### Installing Chocolatey
1. Open PowerShell as Administrator and run:
   ```powershell
   Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
   ```
2. Close and reopen PowerShell

#### Installing pkg-config
1. Using Chocolatey:
   ```bash
   choco install pkgconfiglite
   ```
   
2. Using MSYS2:
   ```bash
   pacman -S mingw-w64-x86_64-pkg-config
   ```

### macOS
Using Homebrew:
```bash
brew install pkg-config
```

### Linux (Debian/Ubuntu)
```bash
sudo apt-get install pkg-config
```

### Linux (Fedora)
```bash
sudo dnf install pkgconfig
```

## Configuring CMake to Use pkg-config

1. Ensure pkg-config is in your system PATH
2. In your CMakeLists.txt, include:
   ```cmake
   find_package(PkgConfig REQUIRED)
   ```

3. To find a package using pkg-config:
   ```cmake
   pkg_check_modules(PREFIX REQUIRED library-name)
   ```

## Verifying Installation

Check if pkg-config is properly installed:
```bash
pkg-config --version
```

## Common Issues and Solutions

1. **pkg-config not found**
   - Verify installation
   - Check if it's in your system PATH

2. **Package not found**
   - Ensure the .pc files are in the PKG_CONFIG_PATH
   - Set PKG_CONFIG_PATH environment variable:
     ```bash
     export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
     ```

## Using with Visual Studio

When using Visual Studio:
1. Install pkg-config using one of the Windows methods above
2. Add pkg-config to your system PATH
3. Restart Visual Studio to recognize the new PATH

## Example Usage in CMakeLists.txt

```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

add_executable(myapp main.cpp)
target_link_libraries(myapp ${SQLITE3_LIBRARIES})
target_include_directories(myapp PRIVATE ${SQLITE3_INCLUDE_DIRS})
```
