#include "pathfinder.h"

PathFinder::PathFinder()
{
}

void PathFinder::moveTo(QQuickItem *item, const QPointF &pos)
{
    ItemData itemData;
    itemData.targetPos = pos;
    mData.insert(item, itemData);
}
