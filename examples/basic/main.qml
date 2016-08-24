import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import QuickPath 1.0

import Example 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property string currentPathType: patherButtonGroup.checkedButton.text
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

    QuickDirectPather {
        id: directPather
        timer: gameTimer
    }

    HackyPassabilityAgent {
        id: hackyPassabilityAgent
        gridItem: grid
    }

    QuickGridPather {
        id: gridPather
        timer: gameTimer
        passabilityAgent: hackyPassabilityAgent

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
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onPressed: {
            var targetX = mouseX;
            var targetY = mouseY;

            if (currentPather === gridPather) {
                if (mouse.button === Qt.LeftButton) {
                    grid.resetColours();
                }

                // Make the target pos in the centre of a tile.
                var column = Math.floor(targetX / gridPather.cellSize);
                var row = Math.floor(targetY / gridPather.cellSize);
                targetX = column * gridPather.cellSize + gridPather.cellSize / 2;
                targetY = row * gridPather.cellSize + gridPather.cellSize / 2;
            }

            if (mouse.button === Qt.LeftButton) {
                moveMarkerTo(targetX, targetY);
                currentPather.moveTo(targetEntity, Qt.point(targetX, targetY))
            } else {
                var item = grid.childAt(targetX, targetY);
                if (item) {
                    item.blocksMovement = true;
                }
            }
        }
    }

    ButtonGroup {
        id: patherButtonGroup
        buttons: patherColumnLayout.children
    }

    function switchPather(patherType) {
        currentPather.cancel(targetEntity);
        currentPathType = patherType;
        resetScene();
    }

    Drawer {
        id: drawer
        width: 0.3 * window.width
        height: window.height

        ColumnLayout {
            id: patherColumnLayout
            anchors.fill: parent

            RadioDelegate {
                id: directPatherRadioDelegate
                text: "DirectPather"

                Layout.fillWidth: true

                onClicked: switchPather(text)
            }

            Label {
                text: "Moves an item directly towards a target, disregarding any obstacles"
                color: "#666"
                wrapMode: Label.Wrap

                Layout.margins: directPatherRadioDelegate.padding
                Layout.topMargin: 0
                Layout.fillWidth: true
            }

            RadioDelegate {
                text: "GridPather"
                width: parent.width
                checked: true

                Layout.fillWidth: true
            }

            Label {
                text: "Moves an item towards a target along a grid, moving around any static obstacles in its path"
                color: "#666"
                wrapMode: Label.Wrap

                Layout.margins: directPatherRadioDelegate.padding
                Layout.topMargin: 0
                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
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
                objectName: "tile" + index
                width: gridPather.cellSize
                height: gridPather.cellSize
                color: processed ? (open ? "blue" : "green") : (blocksMovement ? "red" : "transparent")
                opacity: !processed || chosen ? 1 : 0.25
                border.color: processed ? "transparent" : "lightgray"

                property bool processed: false
                property bool open: false
                property bool chosen: false
                property bool blocksMovement: false
            }
        }
    }

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            text: "Left click to move item"
            opacity: 0.5
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: "Right click to add obstacles"
            opacity: 0.5
            Layout.alignment: Qt.AlignHCenter
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
