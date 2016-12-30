#ifndef BOX2DKINETICSTEERINGAGENT_H
#define BOX2DKINETICSTEERINGAGENT_H

#include "steeringagent.h"

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT Box2DKineticSteeringAgent : public SteeringAgent
{
    Q_OBJECT
    Q_PROPERTY(qreal pixelsPerMeter READ pixelsPerMeter WRITE setPixelsPerMeter NOTIFY pixelsPerMeterChanged)

public:
    Box2DKineticSteeringAgent();

    bool steerTo(QuickPather::QuickEntity *entity, const QPointF &pos, qreal delta) override;

    qreal pixelsPerMeter() const;
    void setPixelsPerMeter(qreal pixelsPerMeter);

signals:
    void pixelsPerMeterChanged();

private:
    qreal mPixelsPerMeter;
};

}

#endif // BOX2DKINETICSTEERINGAGENT_H
