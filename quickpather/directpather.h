#ifndef DIRECTPATHER_H
#define DIRECTPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

namespace QuickPather {

class GameTimer;
class SteeringAgent;
class QuickEntity;

class DirectPathData
{
public:
    QPointF targetPos;
};

class QUICKPATHERSHARED_EXPORT DirectPather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QuickPather::GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)
    Q_PROPERTY(QuickPather::SteeringAgent *steeringAgent READ steeringAgent WRITE setSteeringAgent NOTIFY steeringAgentChanged)

public:
    explicit DirectPather(QObject *parent = nullptr);

    Q_INVOKABLE bool moveEntityTo(QuickPather::QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancelEntityMovement(QuickPather::QuickEntity *entity);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

    QuickPather::SteeringAgent *steeringAgent();
    void setSteeringAgent(QuickPather::SteeringAgent *steeringAgent);

signals:
    void timerChanged();
    void steeringAgentChanged();

private slots:
    void timerUpdated(qreal delta);

private:
    GameTimer *mTimer;
    SteeringAgent *mSteeringAgent;
    QHash<QuickEntity*, DirectPathData> mData;
};

}

#endif // DIRECTPATHER_H
