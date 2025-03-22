# ReadMe

Note that this document was edited using the GitHub friendly mark down [format](https://www.markdownguide.org/cheat-sheet/).

This documents conversations with AI and other pertinent bits of info.

## Project Goals

I want to develop a series of applications in Qt that allow me to live stream to Twitch and other RTMP endpoints in situations where network connectivity is not great. I plan on achieving this by deploying software to one or more phones that will take a camera feed and split the traffic to send to multiple endpoints. A term, I think, is called bonding. Ultimately, I want to be using Secure Reliable Transport (SRT) and the C/C++ based library to use that already exists. 

The eventual plan is to stream from a mobile phone camera using two or more cellular connections to eventually target a PC which will use SRT bonding to reconstruct and then reencode in RTMP and then forward this onto Twitch.

My initial challenge will be to break this down into a series of smaller steps and projects so that I can develop these individual components. It is also preferable to do most of the development using Visual Studio to talk to Qt because I'm very familiar with it, but I am aware that it cannot deploy Android projects. So I want to develop Win32-compatible projects first while writing shared libraries that I can then use for Android projects later in Qt Creator.

## Steps to Achieve the Goal

### Step 1: Simulate a Camera in a Qt Project
1. **Create a Qt Project**: Set up a new Qt project in Visual Studio.
2. **Simulate Camera Feed**: Implement a simulated camera feed using `QtMultimedia`. Display the feed in a `QtQuick` video viewer.

### Step 2: Send Video Over TCP/IP
1. **Create a Second Qt Project**: Set up another Qt project to receive and display the video feed.
2. **Implement TCP/IP Communication**: Use Qt's networking capabilities to send the video feed from the first project to the second project over TCP/IP.
3. **Display Received Video**: Display the received video feed in the second project's `QtQuick` video viewer.

### Step 3: Implement RTMP Protocol
1. **Integrate RTMP Library**: Find and integrate an RTMP library for C++ into your projects.
2. **Send Video Using RTMP**: Modify the first project to send the video feed using the RTMP protocol.
3. **Receive and Display RTMP Video**: Modify the second project to receive and display the video feed using the RTMP protocol.

### Step 4: Transition to SRT and Bonding
1. **Integrate SRT Library**: Find and integrate the SRT library for C++ into your projects.
2. **Implement SRT Bonding**: Develop the logic to split and bond the video feed using multiple network connections.
3. **Test and Optimize**: Test the SRT bonding implementation and optimize for performance and reliability.

### Step 5: Port to Android
1. **Create Shared Libraries**: Refactor your code to create shared libraries that can be used in both Windows and Android projects.
2. **Set Up Qt Creator for Android**: Set up Qt Creator for Android development.
3. **Port Projects to Android**: Port your projects to Android, ensuring they work with the shared libraries.

### Step 6: Finalize and Deploy
1. **Reconstruct and Reencode on PC**: Develop the PC application to receive the bonded SRT streams, reconstruct them, reencode in RTMP, and forward to Twitch.
2. **Test End-to-End**: Test the entire workflow from mobile camera to Twitch.
3. **Deploy and Monitor**: Deploy the applications and monitor their performance in real-world scenarios.

## CMake or QMake?

For new Qt projects, it is generally recommended to use CMake over QMake for several reasons:

1. **Modern and Widely Supported**: CMake is a modern build system that is widely supported and used in the industry. It has better integration with various IDEs, including Visual Studio.
2. **Future-Proof**: Qt has been moving towards CMake as the preferred build system, and future versions of Qt are likely to have better support and features for CMake.
3. **Cross-Platform**: CMake provides excellent cross-platform support, making it easier to manage builds for different platforms, including Windows and Android.

Given your preference for using Visual Studio and the need to eventually deploy to Android, **CMake** would be a better choice. It will provide a smoother experience when transitioning between different platforms and IDEs.

## Issues with QT Camera.

- In Qt 6.2, we need a CaptureSession to manage the connection between camera and video output
- MediaDevices provides access to available camera devices
- The camera needs to have active: true and a specific camera device
- The CaptureSession connects the camera and video output
- The VideoOutput needs an id so it can be referenced by the capture session

## Using CaptureSession for Video Re-encoding in Qt

In Qt if I wanted to re-encode video from an Android camera source, would I use a CaptureSession?

1.	Yes, for Android camera sources in Qt 6.x, CaptureSession is the recommended approach for handling video capture and encoding.
2.	CaptureSession serves as the central component that connects different multimedia elements like Camera and VideoOutput.
3.	For video re-encoding, you would use CaptureSession in conjunction with MediaRecorder.
4.	The implementation would need to capture the Android camera feed, process it, and then encode it for streaming purposes.

## Building OpenSSL

### To Build OpenSSL for Both Windows and Android

#### Step 1: Build OpenSSL for Windows

1. **Download OpenSSL Source Code**  
   - Download the OpenSSL source code from [OpenSSL Source](https://www.openssl.org/source/).

2. **Install Prerequisites**  
   - Install Perl (e.g., [Strawberry Perl](https://strawberryperl.com/)).
   - Install a C compiler (e.g., Visual Studio).

3. **Build OpenSSL**  
   - Open the "x64 Native Tools Command Prompt for VS 2022"... as Admin (for `nmake install`).
   - Navigate to the OpenSSL source directory.
   - Run the following commands:  
     ```
     C:\Strawberry\perl\bin\perl Configure VC-WIN64A
     nmake
     nmake install
     ```
   - This will install OpenSSL binaries and headers in the default location (`C:\Program Files\OpenSSL`).

#### Step 2: Build OpenSSL for Android

1. **Install Android NDK**  
   - Download and install the Android NDK from [Android NDK](https://developer.android.com/ndk).

2. **Set Up Environment**  
   - Add the NDK's `toolchains/llvm/prebuilt/<platform>/bin` directory to your `PATH`.

3. **Build OpenSSL**  
   - Navigate to the OpenSSL source directory.
   - Run the following commands for each Android ABI (e.g., `arm64-v8a`):  
     ```
     ./Configure android-arm64
     make
     make install
     ```
   - Replace `android-arm64` with the appropriate target for other ABIs (e.g., `android-arm`, `android-x86`).

#### Step 3: Update CMake Configuration

- After building OpenSSL, update your `CMakeLists.txt` to use the correct OpenSSL paths for both Windows and Android.

#### Step 4: Verify the Build

1. **For Windows**  
   - Build your project using Visual Studio.

2. **For Android**  
   - Use the following CMake command:  
     ```
     cmake -DCMAKE_TOOLCHAIN_FILE=<path-to-android-ndk>/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21
     ```
   - This setup ensures OpenSSL is built and linked correctly for both Windows and Android.

## Building SRT

### Build for Windows
Open a terminal with the appropriate environment (e.g., Visual Studio Developer Command Prompt).
Run the following commands:
```
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Build for Android
Install the Android NDK and configure the Android toolchain.
Run the following commands:
```
mkdir build_android
cd build_android
cmake .. -DCMAKE_TOOLCHAIN_FILE=<path-to-android-ndk>/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-21
cmake --build . --config Release
```
This setup allows you to build the SRT project alongside your main project for both Windows and Android.

## Other Project Prerequisites
- [PkgConfig Setup Guide](pkgconfig_setup.md) - Instructions for installing and configuring PkgConfig with CMake
- [Vcpkg Setup Guide](vcpkg_setup.md) - Instructions for installing and configuring vcpkg with CMake

Used by RTMPViewer...
```
vcpkg\vcpkg install gstreamer[plugins-bad] --recurse
```

## See also
- [Stream Info](streaminfo.md) - Some info on RTMP, SRT and tooling.

# Project Documentation

## Overview
This project involves video encoding and streaming using Qt.

## Documentation Links

### Qt Camera Documentation
For detailed information on the Camera module in Qt, refer to the official Qt documentation:
- [Qt Camera Documentation](https://doc.qt.io/qt-6/qml-qtmultimedia-camera.html)

### Qt Version
Ensure you are referring to the documentation for the specific version of Qt being used in this project. This project uses Qt 6.8.2.

### Additional Resources
- [Qt Multimedia Overview](https://doc.qt.io/qt-6/qtmultimedia-index.html)
- [Qt QML Types](https://doc.qt.io/qt-6.8/qmltypes.html)