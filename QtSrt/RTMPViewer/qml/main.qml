import QtQuick 2.15
import QtQuick.Controls 2.15
import CustomComponents 1.0

// docker start rtmp-server
// ffmpeg -f lavfi -i testsrc2=size=640x360:rate=25 -c:v libx264 -preset ultrafast -b:v 500k -pix_fmt yuv420p -f flv rtmp://localhost:1935/live/martstest
ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "RTMP Viewer"

    VideoPlayer {
        anchors.fill: parent
        source: "rtmp://localhost:1935/live/martstest"
    }
}
