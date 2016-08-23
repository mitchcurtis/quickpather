#ifndef DIRECTPATHER_H
#define DIRECTPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

class GameTimer;
class QuickEntity;
class SteeringAgent;

class DirectPathData
{
public:
    QPointF targetPos;
};

class QUICKPATHERSHARED_EXPORT DirectPather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    DirectPather();

    Q_INVOKABLE void moveTo(QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancel(QuickEntity *entity);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

signals:
    void timerChanged();

private slots:
    void timerUpdated(qreal delta);

private:
    GameTimer *mTimer;
    SteeringAgent *mSteeringAgent;
    QHash<QuickEntity*, DirectPathData> mData;
};

#endif // DIRECTPATHER_H
