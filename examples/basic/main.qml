import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import QuickPath 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Component.onCompleted: gameTimer.start()

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    DirectPathFinder {
        id: pathFinder

        timer: gameTimer
    }

    GameTimer {
        id: gameTimer
    }

    Rectangle {
        id: targetItem
        x: window.width / 2
        y: window.height / 2
        width: 20
        height: 20
        color: "blue"

        Rectangle {
            color: "steelblue"
            width: 2
            height: 10
            x: parent.width / 2 - width / 2
        }

        QuickEntity {
            id: targetEntity
            item: targetItem
            speed: speedSlider.position * speedSlider.to
        }
    }

    Rectangle {
        id: destinationMarker
        width: 10
        height: width
        color: "transparent"
        border.color: "red"
        radius: width / 2
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            destinationMarker.x = mouseX - destinationMarker.width / 2;
            destinationMarker.y = mouseY - destinationMarker.height / 2;
            pathFinder.moveTo(targetEntity, Qt.point(mouseX, mouseY))
        }
    }

    Label {
        text: "Click to move item"
        opacity: 0.5
        anchors.centerIn: parent
    }

    footer: RowLayout {
        Label {
            text: "Speed"
        }

        Slider {
            id: speedSlider
            from: 0
            value: 50
            to: 300

            ToolTip {
                parent: speedSlider.handle
                visible: speedSlider.pressed
                text: (speedSlider.position * speedSlider.to).toFixed(1)
            }
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            text: "Paused"
        }

        Switch {
            id: pauseSwitch
            onCheckedChanged: gameTimer.togglePaused()
        }
    }
}
