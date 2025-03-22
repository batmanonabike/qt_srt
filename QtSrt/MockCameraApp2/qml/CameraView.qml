import QtQuick
import QtQuick.Controls
import QtMultimedia

Item {
    property alias videoSink: output.videoSink

    VideoOutput {
        id: output
        anchors.fill: parent
    }
}