#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <QPointF>

#include "quickpather_global.h"

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT AbstractEntity
{
public:
    virtual QPointF centrePos() const = 0;
    virtual void setCentrePos(const QPointF &centrePos) = 0;

    virtual qreal speed() const = 0;
    virtual void setSpeed(qreal speed) = 0;

    virtual qreal rotation() const = 0;
    virtual void setRotation(qreal rotation) = 0;
};

}

#endif // ABSTRACTENTITY_H
