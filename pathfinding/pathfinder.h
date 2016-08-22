#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "pathfinding_global.h"

#include <QQuickItem>
#include <QHash>

class GameTimer;

class ItemData
{
public:
    QPointF targetPos;
    QVector<QPointF> nodes;
};

class PATHFINDINGSHARED_EXPORT PathFinder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    PathFinder();

    Q_INVOKABLE void moveTo(QQuickItem *item, const QPointF &pos);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

signals:
    void timerChanged();

private slots:
    void timerUpdated(float delta);

private:
    GameTimer *mTimer;
    QHash<QQuickItem*, ItemData> mData;
};

#endif // PATHFINDER_H
