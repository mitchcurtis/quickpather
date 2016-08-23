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

    property string currentPather: "DirectPather"

    Component.onCompleted: {
        resetScene();
        gameTimer.start();
    }

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    GameTimer {
        id: gameTimer
    }

    DirectPather {
        id: pathFinder
        timer: gameTimer
    }

    DirectPather {
        id: gridFinder
        timer: gameTimer
    }

    header: ToolBar {
        ToolButton {
            text: "Pathers"
            onClicked: drawer.open()
        }
    }

    function resetScene() {
        targetItem.x = window.width / 2;
        targetItem.y = window.height / 2;
    }

    Rectangle {
        id: targetItem
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

    ButtonGroup {
        id: buttonGroup
    }

    Drawer {
        id: drawer
        width: 0.3 * window.width
        height: window.height

        ListView {
            anchors.fill: parent
            model: ["DirectPather", "GridPather"]
            delegate: RadioDelegate {
                checked: currentPather == modelData
                text: modelData
                width: parent.width

                onClicked: currentPather = modelData

                ButtonGroup.group: buttonGroup
            }
        }
    }

    Label {
        text: "Click to move item"
        opacity: 0.5
        anchors.centerIn: parent
    }

    footer: RowLayout {
        Label {
            text: "Entity speed"
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
            text: "Game timer paused"
        }

        Switch {
            id: pauseSwitch
            onCheckedChanged: gameTimer.togglePaused()
        }
    }
}
