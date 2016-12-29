#include "quickgridpather.h"

#include "quickentity.h"

namespace QuickPather {

QuickGridPather::QuickGridPather(QObject *parent) :
    GridPather(parent)
{
}
#ifdef EXPOSE_VISUALISATION_API
void QuickGridPather::onNodeAddedToClosedList(const QPointF &centrePos)
{
    emit nodeAddedToClosedList(centrePos);
}

void QuickGridPather::onNodeAddedToOpenList(const QPointF &centrePos)
{
    emit nodeAddedToOpenList(centrePos);
}

void QuickGridPather::onNodeChosen(const QPointF &centrePos)
{
    emit nodeChosen(centrePos);
}
#endif

}
