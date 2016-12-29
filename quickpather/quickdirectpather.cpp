#include "quickdirectpather.h"

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
    mSteeringAgent(new SteeringAgent(this))
{
}

void DirectPather::moveEntityTo(QuickEntity *entity, const QPointF &pos)
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

void DirectPather::cancelEntityMovement(QuickEntity *entity)
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

    mTimer = timer;

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &DirectPather::timerUpdated);

    emit timerChanged();
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
