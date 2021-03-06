#include "hackypassabilityagent.h"

#include <QQuickItem>
#include <QQuickWindow>

#include "quickentity.h"
#include "utils.h"

HackyPassabilityAgent::HackyPassabilityAgent() :
    mGridItem(nullptr)
{
}

bool HackyPassabilityAgent::isPassable(const QPointF &pos, QuickPather::QuickEntity *entity)
{
    if (!mGridItem)
        return false;

    QuickPather::QuickEntity *quickEntity = dynamic_cast<QuickPather::QuickEntity*>(entity);
    Q_ASSERT(quickEntity);

    // very basic, hacky check that doesn't take into account a radius.
    QQuickItem *child = mGridItem->childAt(pos.x(), pos.y());
    if (child && child->property("blocksMovement").toBool()) {
        return false;
    }

    return true;
}

QQuickItem *HackyPassabilityAgent::gridItem() const
{
    return mGridItem;
}

void HackyPassabilityAgent::setGridItem(QQuickItem *gridItem)
{
    if (gridItem == mGridItem)
        return;

    mGridItem = gridItem;
    emit gridItemChanged();
}
