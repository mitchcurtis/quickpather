#ifndef QUICKGRIDPATHER_H
#define QUICKGRIDPATHER_H

#include "passabilityagent.h"
#include "gridpather.h"

#define EXPOSE_VISUALISATION_API

namespace QuickPather {

class QuickEntity;

class QUICKPATHERSHARED_EXPORT QuickGridPather : public GridPather
{
    Q_OBJECT
    Q_PROPERTY(int cellSize READ cellSize WRITE setCellSize NOTIFY cellSizeChanged)

public:
    explicit QuickGridPather(QObject *parent = 0);

    Q_INVOKABLE void moveTo(QuickPather::QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancel(QuickPather::QuickEntity *entity);

protected:
    virtual void onCellSizeChanged(int oldCellSize, int newCellSize) override;

#ifdef EXPOSE_VISUALISATION_API
    virtual void onNodeAddedToClosedList(const QPointF &centrePos);
    virtual void onNodeAddedToOpenList(const QPointF &centrePos);
    virtual void onNodeChosen(const QPointF &centrePos);
#endif

signals:
    void cellSizeChanged();

#ifdef EXPOSE_VISUALISATION_API
    void nodeAddedToClosedList(const QPointF &centrePos);
    void nodeAddedToOpenList(const QPointF &centrePos);
    void nodeChosen(const QPointF &centrePos);
#endif
};

}

#endif // QUICKGRIDPATHER_H
