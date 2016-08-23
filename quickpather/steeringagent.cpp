#include "steeringagent.h"

#include <QQuickItem>

#include "quickentity.h"
#include "utils.h"

SteeringAgent::SteeringAgent(QObject *parent) :
    QObject(parent)
{
}

bool isNextToTargetPos(QQuickItem *item, const QPointF &targetPos, qreal targetLeniency)
{
    return Utils::fuzzyCompare(Utils::centrePosition(item), targetPos, targetLeniency);
}

void SteeringAgent::steerTo(QuickEntity *entity, const QPointF &pos, qreal delta)
{
    QQuickItem *item = entity->item();
    const qreal targetLeniency = qMax(1.0, entity->speed() * 0.05);
    if (!isNextToTargetPos(item, pos, targetLeniency)) {
        const qreal angleToTarget = Utils::directionTo(Utils::centrePosition(item), pos) + 90;
        item->setRotation(angleToTarget);

        const QPointF newPos = Utils::moveBy(item->position(), angleToTarget, entity->speed() * delta);
        item->setPosition(newPos);
    }
}
