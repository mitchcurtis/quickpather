import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import Box2D 2.0 as Box2D

import QuickPather 1.0

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

    Box2DKineticSteeringAgent {
        id: box2dSteeringAgent
    }

    DirectPather {
        id: directPather
        timer: gameTimer
        steeringAgent: box2dSteeringAgent
    }

    GridPather {
        id: gridPather
        timer: gameTimer
        passabilityAgent: Box2DPassabilityAgent {
            gridItem: grid
        }
        steeringAgent: box2dSteeringAgent

        onNodeAddedToClosedList: {
            var item = grid.childAt(centrePos.x, centrePos.y);
            if (item && !item.blocksMovement) {
                item.processed = true;
                item.open = false;
            }
        }

        onNodeAddedToOpenList: {
            var item = grid.childAt(centrePos.x, centrePos.y);
            if (item && !item.blocksMovement) {
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
                currentPather.moveEntityTo(targetEntity, Qt.point(targetX, targetY))
            } else {
                var item = grid.childAt(targetX, targetY);
                if (item) {
                    item.blocksMovement = true;
                    // TODO: why do we need to do this so that the red shows up?
                    grid.resetColours();
                }
            }
        }
    }

    // Left as a reminder not to set a header so that the
    // bounding boxes aren't "strangely" offset :)
    header: Item {}

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
                id: tile
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

                Box2D.Body {
                    world: physicsWorld
                    target: tile
                    bodyType: Box2D.Body.Static

                    Box2D.Box {
                        x: 2
                        y: 2
                        width: tile.width - 4
                        height: tile.height - 4
                        sensor: !tile.blocksMovement
                    }
                }
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

    Box2D.World {
        id: physicsWorld
        gravity: Qt.point(0, 0)
    }

    Box2D.DebugDraw {
        id: debugDraw
        world: physicsWorld
        anchors.fill: parent
        opacity: 0.75
        visible: debugDrawSwitch.checked
    }

    Wall {
        id: northWall
        x: 0
        y: -height
        width: window.width
        height: 20
    }
    Wall {
        id: southWall
        x: westWall.x + westWall.width
        y: window.height - footer.height - height
        width: window.width
        height: 20
    }
    Wall {
        id: eastWall
        x: window.width
        y: northWall.y + northWall.height
        width: 20
        height: window.contentItem.height
    }
    Wall {
        id: westWall
        x: -width
        y: northWall.y + northWall.height
        width: 20
        height: window.contentItem.height
    }

    Component {
        id: ballComponent

        Rectangle {
            id: ball
            width: 30
            height: 30
            radius: width / 2
            color: "grey"
            opacity: 0.5

            property alias body: ballBody

            Box2D.Body {
                id: ballBody
                world: physicsWorld
                target: ball
                bodyType: Box2D.Body.Dynamic

                Box2D.Circle {
                    x: ball.width / 2 - radius
                    y: ball.height / 2 - radius
                    radius: ball.width / 2
                    density: 1
                    friction: 0.3
                    restitution: 0.5
                }
            }
        }
    }

    Timer {
        running: true
        interval: 3000
        repeat: true

        property int ballsToCreate: 10
        property int ballsCreated: 0

        onTriggered: {
            if (ballsCreated++ < ballsToCreate) {
                var ball = ballComponent.createObject(window.contentItem,
                    { x: 40, y: window.height / 2, z: 1, world: physicsWorld });
                var forceAmount = 10;
                var force = Qt.point(Math.random() * forceAmount, Math.random() * forceAmount);
                ball.body.applyLinearImpulse(force, ball.mapToItem(null, ball.width, ball.height));
            }
        }
    }

    Rectangle {
        id: targetItem
        width: 20
        height: 20
        color: "blue"

        property alias body: targetBody

        Rectangle {
            color: "steelblue"
            width: 2
            height: 10
            x: parent.width / 2 - width / 2
        }

        Box2D.Body {
            id: targetBody
            world: physicsWorld
            target: targetItem
            bodyType: Box2D.Body.Kinematic

            Box2D.Box {
                x: 2
                y: 2
                width: targetItem.width - 4
                height: targetItem.height - 4
            }
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

    ButtonGroup {
        id: patherButtonGroup
        buttons: patherColumnLayout.children
    }

    function switchPather(patherType) {
        currentPather.cancelEntityMovement(targetEntity);
        currentPathType = patherType;
        resetScene();
    }

    Button {
        text: "Pathers"
        onClicked: drawer.open()
        z: 10
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

            Label {
                text: "Debug draw"
            }

            Switch {
                id: debugDrawSwitch
            }
        }
    }
}
