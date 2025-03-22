import QtQuick 2.15
import QtQuick.Controls 2.15
import CustomComponents 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "RTMP Viewer"

    VideoPlayer {
        anchors.fill: parent
        source: "rtmp://your-rtmp-server/live/stream"
    }
}
