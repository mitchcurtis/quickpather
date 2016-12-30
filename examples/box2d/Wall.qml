import QtQuick 2.7
import Box2D 2.0 as Box2D

Item {
    id: wall

    property alias world: body.world

    Box2D.Body {
        id: body
        target: wall

        Box2D.Box {
            width: wall.width
            height: wall.height
        }
    }
}
