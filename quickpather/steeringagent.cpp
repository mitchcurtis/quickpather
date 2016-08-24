#include "steeringagent.h"

#include <QQuickItem>

#include "abstractentity.h"
#include "utils.h"

SteeringAgent::SteeringAgent(QObject *parent) :
    QObject(parent)
{
}

bool SteeringAgent::steerTo(AbstractEntity *entity, const QPointF &pos, qreal delta)
{
    if (!Utils::isNextToTargetPos(entity, pos)) {
        const qreal angleToTarget = Utils::directionTo(entity->centrePos(), pos) + 90;
        entity->setRotation(angleToTarget);

        const QPointF newPos = Utils::moveBy(entity->centrePos(), angleToTarget, entity->speed() * delta);
        entity->setCentrePos(newPos);
        return false;
    }

    return true;
}
