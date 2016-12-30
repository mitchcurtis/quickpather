#include "box2dpassabilityagent.h"

#include <QQuickItem>
#include <QQuickWindow>

#include "quickentity.h"
#include "utils.h"

Box2DPassabilityAgent::Box2DPassabilityAgent() :
    mGridItem(nullptr)
{
}

bool Box2DPassabilityAgent::isPassable(const QPointF &pos, QuickPather::QuickEntity *entity)
{
    if (!mGridItem)
        return false;

    QuickPather::QuickEntity *quickEntity = dynamic_cast<QuickPather::QuickEntity*>(entity);
    Q_ASSERT(quickEntity);

    // very basic, hacky check that doesn't take into account a radius.
    // TODO: this is copied from HackyPassabilityAgent.. we could perhaps try exposing
    // the QueryAABB function to qmlbox2d and then using that here instead?
    // or maybe a simple raycast to each node?
    QQuickItem *child = mGridItem->childAt(pos.x(), pos.y());
    if (child && child->property("blocksMovement").toBool()) {
        return false;
    }

    return true;
}

QQuickItem *Box2DPassabilityAgent::gridItem() const
{
    return mGridItem;
}

void Box2DPassabilityAgent::setGridItem(QQuickItem *gridItem)
{
    if (gridItem == mGridItem)
        return;

    mGridItem = gridItem;
    emit gridItemChanged();
}
