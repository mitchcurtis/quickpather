#include "quickentity.h"

#include <QQuickItem>

#include "utils.h"

namespace QuickPather {

QuickEntity::QuickEntity(QObject *parent) :
    QObject(parent),
    mItem(nullptr),
    mSpeed(10)
{
}

QPointF QuickEntity::centrePos() const
{
    if (!mItem) {
        return QPointF();
    }

    return Utils::centrePosition(mItem);
}

void QuickEntity::setCentrePos(const QPointF &centrePos)
{
    mItem->setPosition(Utils::topLeftFromCentrePosition(mItem, centrePos));
}

qreal QuickEntity::speed() const
{
    return mSpeed;
}

void QuickEntity::setSpeed(qreal speed)
{
    if (speed == mSpeed)
        return;

    mSpeed = speed;
    emit speedChanged();
}

qreal QuickEntity::rotation() const
{
    return mItem->rotation();
}

void QuickEntity::setRotation(qreal rotation)
{
    mItem->setRotation(rotation);
}

QQuickItem *QuickEntity::item() const
{
    return mItem;
}

void QuickEntity::setItem(QQuickItem *item)
{
    if (item == mItem)
        return;

    if (mItem) {
        mItem->disconnect(this);
    }

    mItem = item;

    if (mItem) {
        connect(mItem, &QQuickItem::xChanged, this, &QuickEntity::centrePosChanged);
        connect(mItem, &QQuickItem::yChanged, this, &QuickEntity::centrePosChanged);
        connect(mItem, &QQuickItem::rotationChanged, this, &QuickEntity::rotationChanged);
    }

    emit itemChanged();
}

}
