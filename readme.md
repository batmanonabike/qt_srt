
# ReadMe

Note that this document was edited using the GitHub friendly mark down [format](https://www.markdownguide.org/cheat-sheet/).

This documents conversations with AI and other pertinent bits of info.

# Project Goals

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
