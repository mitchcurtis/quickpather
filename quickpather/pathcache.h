#ifndef PATHCACHE_H
#define PATHCACHE_H

#include <QHash>
#include <QObject>

#include "quickpather_global.h"
#include "gridpather.h"

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT PathCache : public QObject
{
    Q_OBJECT
public:
    explicit PathCache(QObject *parent = 0);

    virtual GridPathData cachedData(QuickPather::QuickEntity *entity, const QPointF &targetPos) const;
    virtual void addCachedData(QuickPather::QuickEntity *entity, const QPointF &targetPos, const GridPathData &pathData);
    virtual void clear();

signals:

public slots:

protected:
    virtual uint hash(QuickPather::QuickEntity *entity, const QPointF &targetPos) const;

private:
    QHash<uint, GridPathData> mCache;
};

}

#endif // PATHCACHE_H
