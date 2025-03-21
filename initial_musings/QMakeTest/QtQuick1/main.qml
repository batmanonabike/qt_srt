import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        text: qsTr("Click Me")
        anchors.centerIn: parent
        onClicked: {
            console.log("Button clicked")
        }
    }
}
