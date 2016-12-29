#include "steeringagent.h"

#include <QQuickItem>

#include "abstractentity.h"
#include "utils.h"

namespace QuickPather {

SteeringAgent::SteeringAgent(QObject *parent) :
    QObject(parent)
{
}

static const qreal lenience = 0.005;

bool SteeringAgent::steerTo(AbstractEntity *entity, const QPointF &pos, qreal delta)
{
    // We want to get as close as possible...
    if (!Utils::isNextToTargetPos(entity, pos, lenience)) {
        const qreal angleToTarget = Utils::directionTo(entity->centrePos(), pos) + 90;
        entity->setRotation(angleToTarget);

        // ... without stopping too early. It's OK if we overshoot the target
        // with the "entity->speed() * delta" calculation, because we choose the
        // remaining distance instead in that case.
        qreal moveDistance = entity->speed() * delta;
        const QLineF lineToTarget(entity->centrePos(), pos);
        if (lineToTarget.length() < moveDistance) {
             moveDistance = lineToTarget.length();
        }
        const QPointF newPos = Utils::moveBy(entity->centrePos(), angleToTarget, moveDistance);
        entity->setCentrePos(newPos);
        return Utils::isNextToTargetPos(entity, pos, lenience);
    }

    return true;
}

}
