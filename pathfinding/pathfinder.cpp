#include "pathfinder.h"

#include <QDebug>

#include "gametimer.h"

PathFinder::PathFinder() :
    mTimer(nullptr)
{
}

void PathFinder::moveTo(QQuickItem *item, const QPointF &pos)
{
    if (!mTimer) {
        qWarning() << "No timer set";
        return;
    }

    ItemData itemData;
    itemData.targetPos = pos;
    mData.insert(item, itemData);
}

GameTimer *PathFinder::timer() const
{
    return mTimer;
}

void PathFinder::setTimer(GameTimer *timer)
{
    if (timer == mTimer)
        return;

    if (mTimer)
        mTimer->disconnect(this);

    mTimer = timer;

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &PathFinder::timerUpdated);

    emit timerChanged();
}

void PathFinder::timerUpdated(float delta)
{
    qDebug() << "yep" << delta;
}
