#ifndef STEERINGAGENT_H
#define STEERINGAGENT_H

#include <QObject>

class QPointF;

namespace QuickPather {

class AbstractEntity;

class SteeringAgent : public QObject
{
    Q_OBJECT

public:
    SteeringAgent(QObject *parent = nullptr);

    bool steerTo(AbstractEntity *entity, const QPointF &pos, qreal delta);
};

}

#endif // STEERINGAGENT_H
