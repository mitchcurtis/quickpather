#ifndef DIRECTPATHFINDER_H
#define DIRECTPATHFINDER_H

#include "pathfinding_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

class GameTimer;
class QuickEntity;

class DirectPathData
{
public:
    QPointF targetPos;
};

class PATHFINDINGSHARED_EXPORT DirectPathFinder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    DirectPathFinder();

    Q_INVOKABLE void moveTo(QuickEntity *entity, const QPointF &pos);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

signals:
    void timerChanged();

private slots:
    void timerUpdated(float delta);

private:
    GameTimer *mTimer;
    QHash<QuickEntity*, DirectPathData> mData;
};

#endif // DIRECTPATHFINDER_H
