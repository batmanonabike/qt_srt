# Stream Info

Note that this document was edited using the GitHub friendly mark down [format](https://www.markdownguide.org/cheat-sheet/).

Some info on RTMP, SRT and tooling.

## Creating a Looping RTMP Stream with FFmpeg

FFmpeg is a powerful tool for creating and manipulating video streams. Here's how to set up a looping RTMP stream for testing your RTMP Viewer application.

### Prerequisites

1. **Install FFmpeg**
   - Windows: Download from [ffmpeg.org](https://ffmpeg.org/download.html) and add to your PATH.
  Or from Admin command prompt...
```
choco install ffmpeg-full
```
   - Linux (Ubuntu/Debian): `sudo apt install ffmpeg`
   - macOS: `brew install ffmpeg`

2. **Set up a local RTMP server** (if you don't have a remote one)
   - Using Docker (easiest method):
```
docker run -d -p 1935:1935 --name rtmp-server tiangolo/nginx-rtmp
```

### Basic Looping Command

To create a continuous looping RTMP stream from a video file:
```
ffmpeg -re -stream_loop -1 -i input_video.mp4 -c:v libx264 -preset veryfast -b:v 1500k -c:a aac -b:a 128k -f flv rtmp://localhost:1935/live/test
```

Command breakdown:
- `-re`: Read input at native frame rate (real-time)
- `-stream_loop -1`: Loop the input video indefinitely (-1 means forever)
- `-i input_video.mp4`: Path to your input video file
- `-c:v libx264`: Use H.264 video codec (widely supported)
- `-preset veryfast`: Encoding speed preset (faster = less compression)
- `-b:v 1500k`: Video bitrate (adjust as needed)
- `-c:a aac`: Use AAC audio codec
- `-b:a 128k`: Audio bitrate
- `-f flv`: Output format (FLV container for RTMP)
- `rtmp://localhost:1935/live/test`: RTMP destination URL

### Sample Video Files

If you need test videos, use these royalty-free samples:
- [Big Buck Bunny (MP4, 64MB)](https://download.blender.org/peach/bigbuckbunny_movies/BigBuckBunny_320x180.mp4)
- [Tears of Steel (MP4, 159MB)](https://download.blender.org/demo/movies/ToS/ToS-4k-1920.mp4)
NOTE: These didnt work when I tested them.

### Advanced Options

#### Adjusting Video Quality

For higher quality:
```
ffmpeg -re -stream_loop -1 -i input.mp4 -c:v libx264 -preset slower -crf 22 -c:a aac -b:a 192k -f flv rtmp://localhost:1935/live/test
```

For lower bandwidth usage:
```
ffmpeg -re -stream_loop -1 -i input.mp4 -c:v libx264 -preset veryfast -crf 28 -c:a aac -b:a 96k -f flv rtmp://localhost:1935/live/test
```

#### Creating a Stream from Images

You can also create a slideshow from image files:
```
ffmpeg -re -loop 1 -framerate 1 -pattern_type glob -i "images/*.jpg" -c:v libx264 -pix_fmt yuv420p -t 3600 -f flv rtmp://localhost:1935/live/slideshow
```

#### Streaming Desktop Screen

To stream your desktop with looping audio:
```
ffmpeg -f gdigrab -framerate 30 -i desktop -f lavfi -i "sine=frequency=1000:duration=3600" -c:v libx264 -preset veryfast -pix_fmt yuv420p -c:a aac -f flv rtmp://localhost:1935/live/desktop
```

You can verify the stream in VLC using the same RTMP URL.

### Troubleshooting

- **High CPU Usage**: Try using a hardware encoder if available (`-c:v h264_nvenc` for NVIDIA GPUs)
- **Stuttering Playback**: Reduce bitrate or use a less demanding preset
- **Connection Refused**: Ensure your RTMP server is running and port 1935 is accessible
- **FFmpeg Errors**: Make sure your input file is valid and codec parameters are correct

### Stop Streaming

To stop the FFmpeg process:
- In Windows: Press `Ctrl+C` in the command prompt
- In Linux/macOS: Press `Ctrl+C` in the terminal

For a graceful shutdown of the Docker container:
```
docker stop rtmp-server
```

## Testing RTMP Streams in VLC Media Player

Testing RTMP streams in VLC before implementing them in your custom application offers several advantages:

1. Quickly verify stream availability and quality
2. Troubleshoot network connectivity issues
3. Confirm RTMP URL format and parameters
4. Save development time by pre-validating streams

## Steps to Test RTMP Streams in VLC

1. **Install VLC Media Player**
   - Download and install VLC from [the official website](https://www.videolan.org/vlc/)

2. **Open the Network Stream**
   - Launch VLC Media Player
   - Go to **Media > Open Network Stream** (or press **Ctrl+N**)
   - In the "Please enter a network URL" field, paste your RTMP URL

3. **Enter Your RTMP URL**
   - Format: `rtmp://streaming.idopterlabs.com/live/stream`
   - Example URLs to test:

```
	rtmp://streaming.idopterlabs.com/live/stream
	rtmp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4
```

4. **Click "Play"**
   - If the stream is valid and accessible, VLC will begin playback
   - You may experience a brief delay as the initial connection and buffering occur

## Troubleshooting

If you encounter issues when testing an RTMP stream in VLC:

- **Stream Not Playing**:
  - Verify the RTMP URL is correct
  - Check if the stream is currently active
  - Ensure your network allows RTMP traffic (port 1935)
  - Try disabling firewall temporarily to rule out network blocking issues

- **Playback Stutters or Lags**:
  - Check your internet connection stability
  - The stream might have bandwidth issues at its source
  - Adjust VLC's network buffer settings in **Tools > Preferences > Input/Codecs**

## Integration with RTMP Viewer Application

If the stream works properly in VLC, you can implement it in your RTMP Viewer application:

1. Update the `source` property in `RTMPViewer/main.qml`:
```
VideoPlayer { anchors.fill: parent source: "rtmp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mp4" }
```

2. The GStreamer-based `VideoPlayer` component will use the provided RTMP URL to create and play the stream through the playbin element.

## Additional Resources

- [VLC Documentation](https://wiki.videolan.org/Documentation:Documentation/)
- [RTMP Protocol Specification](https://www.adobe.com/devnet/rtmp.html)
- [GStreamer Playback Components](https://gstreamer.freedesktop.org/documentation/playback/playbin.html)
