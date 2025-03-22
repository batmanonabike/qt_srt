import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
import com.example.camera 1.0

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: "Mock Camera App"

    CameraController {
        id: cameraController
        active: true
        resolution: Qt.size(640, 480)
        frameRate: 30
        videoSink: videoOutput.videoSink
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        CameraView {
            id: videoOutput
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 10
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.margins: 10
            spacing: 10

            Button {
                text: cameraController.active ? "Stop Camera" : "Start Camera"
                onClicked: cameraController.active = !cameraController.active
            }

            ComboBox {
                id: resolutionCombo
                model: [
                    "320x240", 
                    "640x480", 
                    "1280x720", 
                    "1920x1080"
                ]
                currentIndex: 1
                onActivated: {
                    let parts = currentText.split('x')
                    if (parts.length === 2) {
                        cameraController.resolution = Qt.size(parseInt(parts[0]), parseInt(parts[1]))
                    }
                }
            }

            Label {
                text: "Frame Rate:"
            }

            SpinBox {
                id: frameRateSpinBox
                from: 1
                to: 60
                value: cameraController.frameRate
                onValueModified: cameraController.frameRate = value
            }

            Label {
                text: "Active: " + cameraController.active
            }
        }
    }
}
