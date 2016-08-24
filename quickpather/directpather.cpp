#include "directpather.h"

#include <QDebug>
#include <QTransform>
#include <QQuickItem>

#include "abstractentity.h"
#include "gametimer.h"
#include "steeringagent.h"
#include "utils.h"

DirectPather::DirectPather(QObject *parent) :
    QObject(parent),
    mTimer(nullptr),
    mSteeringAgent(new SteeringAgent(this))
{
}

void DirectPather::moveEntityTo(AbstractEntity *entity, const QPointF &pos)
{
    if (!mTimer) {
        qWarning() << "No timer set";
        return;
    }

    if (!mSteeringAgent) {
        qWarning() << "No steering agent set";
        return;
    }

    DirectPathData pathData;
    pathData.targetPos = pos;
    mData.insert(entity, pathData);
}

void DirectPather::cancelEntityMovement(AbstractEntity *entity)
{
    mData.remove(entity);
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

    GameTimer *oldTimer = mTimer;
    mTimer = timer;

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &DirectPather::timerUpdated);

    onTimerChanged(oldTimer, mTimer);
}

void DirectPather::onTimerChanged(GameTimer *, GameTimer *)
{
}

void DirectPather::timerUpdated(qreal delta)
{
    QHashIterator<AbstractEntity*, DirectPathData> it(mData);
    while (it.hasNext()) {
        it.next();
        AbstractEntity *entity = it.key();
        DirectPathData pathData = it.value();
        if (mSteeringAgent->steerTo(entity, pathData.targetPos, delta)) {
            mData.remove(entity);
        }
    }
}
