#ifndef STEERINGAGENT_H
#define STEERINGAGENT_H

#include <QObject>

#include "quickpather_global.h"

class QPointF;

namespace QuickPather {

class QuickEntity;

class QUICKPATHERSHARED_EXPORT SteeringAgent : public QObject
{
    Q_OBJECT

public:
    SteeringAgent(QObject *parent = nullptr);

    virtual bool steerTo(QuickPather::QuickEntity *entity, const QPointF &pos, qreal delta);
};

}

#endif // STEERINGAGENT_H
