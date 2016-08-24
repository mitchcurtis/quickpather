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

        onNodeAddedToClosedList: {
            var item = grid.childAt(centrePos.x, centrePos.y);
            if (item) {
                item.processed = true;
                item.open = false;
            }
        }

        onNodeAddedToOpenList: {
            var item = grid.childAt(centrePos.x, centrePos.y);
            if (item) {
                item.processed = true;
                item.open = true;
            }
        }

        onNodeChosen: {
            var item = grid.childAt(centrePos.x, centrePos.y);
            if (item) {
                item.chosen = true;
            }
        }
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

            // Remove path visualisations.
            grid.resetColours();
        }
    }

    function moveMarkerTo(x, y) {
        destinationMarker.x = x - destinationMarker.width / 2;
        destinationMarker.y = y - destinationMarker.height / 2;
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressed: {
            var targetX = mouseX;
            var targetY = mouseY;

            if (currentPather === gridPather) {
                grid.resetColours();

                // Make the target pos in the centre of a tile.
                var column = Math.floor(targetX / gridPather.cellSize);
                var row = Math.floor(targetY / gridPather.cellSize);
                targetX = column * gridPather.cellSize + gridPather.cellSize / 2;
                targetY = row * gridPather.cellSize + gridPather.cellSize / 2;
            }

            moveMarkerTo(targetX, targetY);
            currentPather.moveTo(targetEntity, Qt.point(targetX, targetY))
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

    Grid {
        id: grid
        columns: window.width / gridPather.cellSize
        rows: window.height / gridPather.cellSize
        anchors.fill: parent
        visible: currentPather === gridPather

        function resetColours() {
            for (var row = 0; row < rows; ++row) {
                for (var column = 0; column < columns; ++column) {
                    var item = grid.childAt(
                        column * gridPather.cellSize + gridPather.cellSize / 2,
                        row * gridPather.cellSize + gridPather.cellSize / 2);
                    if (item) {
                        item.processed = false;
                        item.open = false;
                        item.chosen = false;
                    }
                }
            }
        }

        Repeater {
            model: grid.columns * grid.rows

            Rectangle {
                width: gridPather.cellSize
                height: gridPather.cellSize
                color: processed ? (open ? "blue" : "green") : "transparent"
                opacity: !processed || chosen ? 1 : 0.25
                border.color: processed ? "transparent" : "lightgray"

                property bool processed: false
                property bool open: false
                property bool chosen: false
            }
        }
    }

    Label {
        text: "Click to move item"
        opacity: 0.5
        anchors.centerIn: parent
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

    footer: ToolBar {
        RowLayout {
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
}
