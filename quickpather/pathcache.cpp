#include "pathcache.h"

#include <QQuickItem>
#include <QtMath>

namespace QuickPather {

PathCache::PathCache(QObject *parent) :
    QObject(parent)
{
}

GridPathData PathCache::cachedData(QuickEntity *entity, const QPointF &targetPos) const
{
    auto it = mCache.find(hash(entity, targetPos));
    if (it != mCache.end())
        return it.value();

    return GridPathData();
}

void PathCache::addCachedData(QuickEntity *entity, const QPointF &targetPos, const GridPathData &pathData)
{
    mCache.insert(hash(entity, targetPos), pathData);
}

void PathCache::clear()
{
    mCache.clear();
}

uint PathCache::hash(QuickEntity *entity, const QPointF &targetPos) const
{
    const QRect bounds(entity->item()->x(), entity->item()->y(), entity->item()->width(), entity->item()->height());
    const QPoint centre = bounds.center();
    const uint hash = qHash(centre.x()) ^
        qHash(centre.y()) ^
        qHash(targetPos.x()) ^
        qHash(targetPos.y());
    return hash;
}

}
