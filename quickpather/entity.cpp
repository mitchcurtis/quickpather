#include "entity.h"

namespace QuickPather {

Entity::Entity(QObject *parent) :
    QObject(parent),
    mSpeed(10),
    mRotation(0)
{
}

QPointF Entity::centrePos() const
{
    return mCentrePos;
}

void Entity::setCentrePos(const QPointF &centrePos)
{
    if (centrePos == mCentrePos)
        return;

    mCentrePos = centrePos;
    emit centrePosChanged();
}

qreal Entity::speed() const
{
    return mSpeed;
}

void Entity::setSpeed(qreal speed)
{
    if (speed == mSpeed)
        return;

    mSpeed = speed;
    emit speedChanged();
}

qreal Entity::rotation() const
{
    return mRotation;
}

void Entity::setRotation(qreal rotation)
{
    if (rotation == mRotation)
        return;

    mRotation = rotation;
    emit rotationChanged();
}

}
