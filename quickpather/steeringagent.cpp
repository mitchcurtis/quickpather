#include "steeringagent.h"

#include <QQuickItem>

#include "quickentity.h"
#include "utils.h"

SteeringAgent::SteeringAgent(QObject *parent) :
    QObject(parent)
{
}

bool SteeringAgent::steerTo(QuickEntity *entity, const QPointF &pos, qreal delta)
{
    QQuickItem *item = entity->item();
    if (!Utils::isNextToTargetPos(entity, pos)) {
        const qreal angleToTarget = Utils::directionTo(Utils::centrePosition(item), pos) + 90;
        item->setRotation(angleToTarget);

        const QPointF newPos = Utils::moveBy(item->position(), angleToTarget, entity->speed() * delta);
        item->setPosition(newPos);
        return false;
    }

    return true;
}
