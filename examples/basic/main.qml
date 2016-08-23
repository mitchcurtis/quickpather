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

    property string currentPathType: "GridPather"
    readonly property var currentPather: currentPathType == "DirectPather" ? directPather : gridPather

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
        id: directPather
        timer: gameTimer
    }

    GridPather {
        id: gridPather
        timer: gameTimer
    }

    header: ToolBar {
        ToolButton {
            text: "Pathers"
            onClicked: drawer.open()
        }
    }

    function resetScene() {
        if (currentPather === directPather) {
            targetItem.x = window.width / 2;
            targetItem.y = window.height / 2;
        } else {
            // Make positions conform to grid.
            var x = gridPather.cellSize * 10.5;
            var y = gridPather.cellSize * 10.5;
            targetItem.x = x - targetItem.width / 2;
            targetItem.y = y - targetItem.height / 2;
            moveMarkerTo(x, y);
        }
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

    function moveMarkerTo(x, y) {
        destinationMarker.x = x - destinationMarker.width / 2;
        destinationMarker.y = y - destinationMarker.height / 2;
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            moveMarkerTo(mouseX, mouseY);
            currentPather.moveTo(targetEntity, Qt.point(mouseX, mouseY))
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
                checked: currentPathType == modelData
                text: modelData
                width: parent.width

                onClicked: {
                    currentPather.cancel(targetEntity);
                    currentPathType = modelData;
                    resetScene();
                }

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
