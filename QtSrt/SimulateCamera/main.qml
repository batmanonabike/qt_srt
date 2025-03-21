import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Simulated Camera Feed"

    Camera {
        id: camera
    }

    VideoOutput {
        anchors.fill: parent
        source: camera
    }
}
