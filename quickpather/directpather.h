#ifndef DIRECTPATHER_H
#define DIRECTPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

class AbstractEntity;
class GameTimer;
class SteeringAgent;

class DirectPathData
{
public:
    QPointF targetPos;
};

class QUICKPATHERSHARED_EXPORT DirectPather : public QObject
{
    Q_OBJECT

public:
    explicit DirectPather(QObject *parent = nullptr);

    void moveEntityTo(AbstractEntity *entity, const QPointF &pos);
    void cancelEntityMovement(AbstractEntity *entity);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

protected:
    virtual void onTimerChanged(GameTimer *oldTimer, GameTimer *newTimer);

private slots:
    void timerUpdated(qreal delta);

private:
    GameTimer *mTimer;
    SteeringAgent *mSteeringAgent;
    QHash<AbstractEntity*, DirectPathData> mData;
};

#endif // DIRECTPATHER_H
