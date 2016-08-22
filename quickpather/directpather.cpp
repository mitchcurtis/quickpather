#include "directpather.h"

#include <QDebug>
#include <QTransform>
#include <QQuickItem>

#include "gametimer.h"
#include "quickentity.h"
#include "mathutils.h"

DirectPather::DirectPather() :
    mTimer(nullptr)
{
}

void DirectPather::moveTo(QuickEntity *entity, const QPointF &pos)
{
    if (!mTimer) {
        qWarning() << "No timer set";
        return;
    }

    DirectPathData pathData;

    QHash<QuickEntity*, DirectPathData>::iterator it = mData.find(entity);
    if (it != mData.end()) {
        pathData = it.value();
    }

    pathData.targetPos = pos;

    // add some nodes eventually

    mData.insert(entity, pathData);
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

static QPointF centrePosition(const QQuickItem *item)
{
    return item->position() + QPointF(item->width() / 2.0, item->height() / 2.0);
}

static bool isNextToTargetPos(QQuickItem *item, const QPointF &targetPos, qreal targetLeniency)
{
    return MathUtils::fuzzyCompare(centrePosition(item), targetPos, targetLeniency);
}

static float directionTo(const QPointF &source, const QPointF &target) {
    QPointF toTarget(target.x() - source.x(), target.y() - source.y());
    float facingTarget = MathUtils::clampAngle(qRadiansToDegrees(atan2(toTarget.y(), toTarget.x())));
    return facingTarget;
}

static float cartesianDirectionTo(const QPointF &source, const QPointF &target) {
    QPointF toTarget(target.x() - source.x(), target.y() - source.y());
    float facingTarget = MathUtils::clampAngle(qRadiansToDegrees(atan2(toTarget.y() * -1, toTarget.x())));
    return facingTarget;
}

static QPointF moveBy(const QPointF &pos, qreal rotation, float distance)
{
    return pos - QTransform().rotate(rotation).map(QPointF(0, distance));
}

void DirectPather::timerUpdated(float delta)
{
    QHashIterator<QuickEntity*, DirectPathData> it(mData);
    while (it.hasNext()) {
        it.next();
        QuickEntity *entity = it.key();
        QQuickItem *item = entity->item();
        DirectPathData pathData = it.value();
        const qreal targetLeniency = qMax(1.0, entity->speed() * 0.05);
        if (!isNextToTargetPos(item, pathData.targetPos, targetLeniency)) {
            const qreal angleToTarget = directionTo(centrePosition(item), pathData.targetPos) + 90;
            item->setRotation(angleToTarget);

            const QPointF newPos = moveBy(item->position(), angleToTarget, entity->speed() * delta);
            item->setPosition(newPos);
        }
    }
}
