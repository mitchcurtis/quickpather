#include "quickentity.h"

#include <QQuickItem>

QuickEntity::QuickEntity(QObject *parent) :
    QObject(parent),
    mItem(nullptr),
    mSpeed(10)
{
}

QQuickItem *QuickEntity::item() const
{
    return mItem;
}

void QuickEntity::setItem(QQuickItem *item)
{
    if (item == mItem)
        return;

    mItem = item;
    emit itemChanged();
}

qreal QuickEntity::speed() const
{
    return mSpeed;
}

void QuickEntity::setSpeed(const qreal &speed)
{
    if (speed == mSpeed)
        return;

    mSpeed = speed;
    emit speedChanged();
}
