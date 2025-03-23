import QtQuick
import QtQuick.Controls
import QtMultimedia

Item {
    property alias videoSink: output.videoSink

    // Render video or camera.
    // Derives from QVideoSink
    VideoOutput {
        id: output
        anchors.fill: parent
    }
}