# Setting up a Unix-like Environment with MSYS on Windows

Note that this document was edited using the GitHub friendly mark down [format](https://www.markdownguide.org/cheat-sheet/).

This document provides step-by-step instructions to set up a Unix-like environment on Windows using MSYS. This environment will allow you to run shell scripts and use Unix commands.

## Installation Steps

### Step 1: Download and Install MSYS2

1. Go to the [MSYS2 website](https://www.msys2.org/) and download the installer.
2. Run the installer and follow the instructions to install MSYS2.

### Step 2: Update MSYS2

1. Open the MSYS2 shell (you can find it in the Start menu).
2. Update the package database and core system packages by running the following commands:
    
```
pacman -Syu
```

3. Close the MSYS2 shell and reopen it.
4. Run the update command again to ensure everything is up to date:

```
pacman -Su
```
    
### Step 3: Install Required Packages

1. Install the necessary build tools and libraries:
```
pacman -S base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake git
pacman -S nasm
pacman -S mingw-w64-x86_64-gcc
```

2. Added these to Windows System Path:
```
C:\msys64\usr\bin
C:\msys64\mingw64\bin
```

## Configuring CMake to Use MSYS2

To use MSYS2 with CMake, you need to configure your `CMakeLists.txt` to use the MSYS2 environment for running shell scripts.  
See projects!

## Common Issues

### Bash Executable Not Found

- Ensure MSYS2 is installed correctly.
- Verify the path to the `bash` executable in the `find_program` command.
- Restart your IDE/terminal after installing MSYS2.

### CMake Can't Find Packages

- Verify package is installed for the correct architecture.
- Check MSYS2 install logs for errors.
- Ensure `CMAKE_TOOLCHAIN_FILE` is set before the `project()` command.

## Additional Resources

- [MSYS2 Website](https://www.msys2.org/)
- [MSYS2 Documentation](https://www.msys2.org/docs/)
- [CMake Documentation](https://cmake.org/documentation/)

