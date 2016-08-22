import QtQuick 2.7
import QtQuick.Window 2.2

import QuickPath 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Component.onCompleted: gameTimer.start()

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    PathFinder {
        id: pathFinder

        timer: gameTimer
    }

    GameTimer {
        id: gameTimer
    }

    Rectangle {
        id: targetItem
        width: 20
        height: 20
        border.color: "red"
    }

    Rectangle {
        id: destination
        width: 20
        height: 20
        border.color: "red"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            pathFinder.moveTo(targetItem, Qt.point(destination.x, destination.y))
        }
    }
}
