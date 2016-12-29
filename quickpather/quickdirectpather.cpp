#include "quickdirectpather.h"

#include <QDebug>
#include <QTransform>
#include <QQuickItem>

#include "gametimer.h"
#include "quickentity.h"
#include "steeringagent.h"
#include "utils.h"

namespace QuickPather {

QuickDirectPather::QuickDirectPather(QObject *parent) :
    QObject(parent),
    mTimer(nullptr),
    mSteeringAgent(new SteeringAgent(this))
{
}

void QuickDirectPather::moveEntityTo(QuickEntity *entity, const QPointF &pos)
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

void QuickDirectPather::cancelEntityMovement(QuickEntity *entity)
{
    mData.remove(entity);
}

GameTimer *QuickDirectPather::timer() const
{
    return mTimer;
}

void QuickDirectPather::setTimer(GameTimer *timer)
{
    if (timer == mTimer)
        return;

    if (mTimer)
        mTimer->disconnect(this);

    mTimer = timer;

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &QuickDirectPather::timerUpdated);

    emit timerChanged();
}

void QuickDirectPather::timerUpdated(qreal delta)
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
