# Setting up vcpkg for CMake Projects

Note that this document was edited using the GitHub friendly mark down [format](https://www.markdownguide.org/cheat-sheet/).

## Installation Steps

1. Clone vcpkg repository:
```bash
git clone https://github.com/Microsoft/vcpkg.git
```

2. Run the bootstrap script:
   - Windows:
   ```bash
   .\vcpkg\bootstrap-vcpkg.bat
   ```
   - Linux/macOS:
   ```bash
   ./vcpkg/bootstrap-vcpkg.sh
   ```

3. Add system environment variable:
   - Set `VCPKG_ROOT` to point to your vcpkg installation directory

4. Integrate vcpkg with CMake:
```bash
vcpkg integrate install
```

## Using vcpkg with CMake

1. Add the following to your CMake project:
```cmake
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
```

2. Install packages using vcpkg:
```bash
vcpkg install [package_name]:x64-windows  # For Windows
vcpkg install [package_name]:x64-linux    # For Linux
vcpkg install [package_name]:x64-osx      # For macOS
```

## Common Issues

### Cannot Find VCPKG_ROOT
- Ensure the environment variable is set correctly
- Restart your IDE/terminal after setting environment variables

### CMake Can't Find Packages
- Verify package is installed for correct architecture
- Check vcpkg install logs for errors
- Ensure CMAKE_TOOLCHAIN_FILE is set before project() command

## Additional Resources
- [vcpkg GitHub Repository](https://github.com/Microsoft/vcpkg)
- [vcpkg Documentation](https://vcpkg.io/en/docs/index.html)
