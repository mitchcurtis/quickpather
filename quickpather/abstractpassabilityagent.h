#ifndef ABSTRACTPASSABILITYAGENT_H
#define ABSTRACTPASSABILITYAGENT_H

#include <QPointF>

#include "quickpather_global.h"

class AbstractEntity;

class QUICKPATHERSHARED_EXPORT AbstractPassabilityAgent
{
public:
    virtual bool isPassable(const QPointF &pos, AbstractEntity *entity) = 0;
};

#endif // ABSTRACTPASSABILITYAGENT_H
