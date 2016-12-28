#include "quickdirectpather.h"

#include "quickentity.h"

namespace QuickPather {

QuickDirectPather::QuickDirectPather(QObject *parent) :
    DirectPather(parent)
{
}

void QuickDirectPather::moveTo(QuickEntity *entity, const QPointF &pos)
{
    moveEntityTo(entity, pos);
}

void QuickDirectPather::cancel(QuickEntity *entity)
{
    cancelEntityMovement(entity);
}

void QuickDirectPather::onTimerChanged(GameTimer *, GameTimer *)
{
    emit timerChanged();
}

}
