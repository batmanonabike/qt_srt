import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: "Simulated Camera Feed"
    
    // Fully simulated video source
    Rectangle {
        id: simulatedVideo
        anchors.fill: parent
        
        // Create a gradient background
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#000044" }
            GradientStop { position: 1.0; color: "#000022" }
        }
        
        // Moving circle to simulate motion
        Rectangle {
            id: movingCircle
            width: 80
            height: 80
            radius: 40
            color: Qt.hsla(hue/360, 0.8, 0.6, 1.0)
            property real hue: 0
            property real xPos: 100
            property real yPos: 100
            property real xVel: 2
            property real yVel: 3
            
            x: xPos
            y: yPos
            
            // Border to make it more visible
            border.width: 2
            border.color: "white"
            
            // Add timestamp text
            Text {
                id: timestamp
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
                font.pixelSize: 14
                text: "00:00:00"
            }
        }
        
        // Timestamp overlay in corner
        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 10
            color: "white"
            font.pixelSize: 16
            text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
            
            Timer {
                interval: 1000
                running: true
                repeat: true
                onTriggered: {
                    parent.text = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
                }
            }
        }
        
        // Simulated camera info
        Text {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10
            color: "white"
            font.pixelSize: 14
            text: "SIMULATED CAMERA"
        }
        
        // Animation timer for the circle
        Timer {
            interval: 16  // ~60fps
            running: true
            repeat: true
            onTriggered: {
                // Update position
                movingCircle.xPos += movingCircle.xVel;
                movingCircle.yPos += movingCircle.yVel;
                
                // Bounce on edges
                if (movingCircle.xPos <= 0 || movingCircle.xPos >= parent.width - movingCircle.width) {
                    movingCircle.xVel = -movingCircle.xVel;
                }
                if (movingCircle.yPos <= 0 || movingCircle.yPos >= parent.height - movingCircle.height) {
                    movingCircle.yVel = -movingCircle.yVel;
                }
                
                // Change color
                movingCircle.hue = (movingCircle.hue + 0.5) % 360;
                
                // Update timestamp
                var date = new Date();
                timestamp.text = Qt.formatTime(date, "hh:mm:ss");
            }
        }
    }
}