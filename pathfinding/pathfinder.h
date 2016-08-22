#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "pathfinding_global.h"

#include <QQuickItem>
#include <QHash>

class ItemData
{
public:
    QPointF targetPos;
    QVector<QPointF> nodes;
};

class PATHFINDINGSHARED_EXPORT PathFinder : public QObject
{
public:
    PathFinder();

    Q_INVOKABLE void moveTo(QQuickItem *item, const QPointF &pos);

private:
    QHash<QQuickItem*, ItemData> mData;
};

#endif // PATHFINDER_H
