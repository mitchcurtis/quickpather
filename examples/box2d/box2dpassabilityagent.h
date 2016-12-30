#ifndef BOX2DPASSABILITYAGENT_H
#define BOX2DPASSABILITYAGENT_H

#include "passabilityagent.h"

class QQuickItem;

class Box2DPassabilityAgent : public QuickPather::PassabilityAgent
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *gridItem READ gridItem WRITE setGridItem NOTIFY gridItemChanged)

public:
    Box2DPassabilityAgent();

    virtual bool isPassable(const QPointF &pos, QuickPather::QuickEntity *entity) override;

    QQuickItem *gridItem() const;
    void setGridItem(QQuickItem *gridItem);

signals:
    void gridItemChanged();

private:
    QQuickItem *mGridItem;
};

#endif // BOX2DPASSABILITYAGENT_H
