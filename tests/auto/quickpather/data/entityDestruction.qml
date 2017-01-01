import QtQuick 2.7

import QuickPather 1.0

Item {
    id: root
    visible: true
    width: 640
    height: 480

    Component.onCompleted: gameTimer.start()

    property alias entity: targetEntity
    property alias gridPather: gridPather

    GameTimer {
        id: gameTimer
    }

    SteeringAgent {
        id: steeringAgent
    }

    GridPather {
        id: gridPather
        timer: gameTimer
        passabilityAgent: PassabilityAgent {}
        steeringAgent: steeringAgent
    }

    Rectangle {
        id: targetItem
        width: 32
        height: 32
        color: "blue"

        QuickEntity {
            id: targetEntity
            item: targetItem
        }
    }
}
