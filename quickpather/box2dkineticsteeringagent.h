#ifndef BOX2DKINETICSTEERINGAGENT_H
#define BOX2DKINETICSTEERINGAGENT_H

#include "steeringagent.h"

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT Box2DKineticSteeringAgent : public SteeringAgent
{
    Q_OBJECT

public:
    Box2DKineticSteeringAgent();

    bool steerTo(QuickPather::QuickEntity *entity, const QPointF &pos, qreal delta) override;
};

}

#endif // BOX2DKINETICSTEERINGAGENT_H
