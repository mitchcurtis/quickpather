#include "directpather.h"

#include <QDebug>
#include <QTransform>
#include <QQuickItem>

#include "gametimer.h"
#include "quickentity.h"
#include "steeringagent.h"
#include "utils.h"

namespace QuickPather {

DirectPather::DirectPather(QObject *parent) :
    QObject(parent),
    mTimer(nullptr),
    mSteeringAgent(nullptr)
{
}

bool DirectPather::moveEntityTo(QuickEntity *entity, const QPointF &pos)
{
    if (!mTimer) {
        qWarning() << "DirectPather: no timer set";
        return false;
    }

    if (!mSteeringAgent) {
        qWarning() << "DirectPather: no steering agent set";
        return false;
    }

    DirectPathData pathData;
    pathData.targetPos = pos;
    mData.insert(entity, pathData);

    QObject::connect(entity, &QuickEntity::entityDestroyed, this, &DirectPather::cancelEntityMovement);

    return true;
}

void DirectPather::cancelEntityMovement(QuickEntity *entity)
{
    mData.remove(entity);
    QObject::disconnect(entity, &QuickEntity::entityDestroyed, this, &DirectPather::cancelEntityMovement);
}

GameTimer *DirectPather::timer() const
{
    return mTimer;
}

void DirectPather::setTimer(GameTimer *timer)
{
    if (timer == mTimer)
        return;

    if (mTimer)
        mTimer->disconnect(this);

    mTimer = timer;

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &DirectPather::timerUpdated);

    emit timerChanged();
}

SteeringAgent *DirectPather::steeringAgent()
{
    return mSteeringAgent;
}

void DirectPather::setSteeringAgent(SteeringAgent *steeringAgent)
{
    if (!mData.isEmpty()) {
        qWarning() << "DirectPather: cannot set steering agent while pathing active";
        return;
    }

    if (steeringAgent == mSteeringAgent)
        return;

    mSteeringAgent = steeringAgent;
    emit steeringAgentChanged();
}

void DirectPather::timerUpdated(qreal delta)
{
    QHashIterator<QuickEntity*, DirectPathData> it(mData);
    while (it.hasNext()) {
        it.next();
        QuickEntity *entity = it.key();
        DirectPathData pathData = it.value();
        if (mSteeringAgent->steerTo(entity, pathData.targetPos, delta)) {
            mData.remove(entity);
        }
    }
}

}
