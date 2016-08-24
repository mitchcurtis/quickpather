#ifndef QUICKGRIDPATHER_H
#define QUICKGRIDPATHER_H

#include "gridpather.h"

#define EXPOSE_VISUALISATION_API

class QuickEntity;

class QUICKPATHERSHARED_EXPORT QuickGridPather : public GridPather
{
    Q_OBJECT
    Q_PROPERTY(int cellSize READ cellSize WRITE setCellSize NOTIFY cellSizeChanged)
    Q_PROPERTY(GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    explicit QuickGridPather(QObject *parent = 0);

    Q_INVOKABLE void moveTo(QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancel(QuickEntity *entity);

protected:
    virtual void onCellSizeChanged(int oldCellSize, int newCellSize) override;
    virtual void onTimerChanged(GameTimer *oldTimer, GameTimer *newTimer) override;

#ifdef EXPOSE_VISUALISATION_API
    virtual void onNodeAddedToClosedList(const QPointF &centrePos);
    virtual void onNodeAddedToOpenList(const QPointF &centrePos);
    virtual void onNodeChosen(const QPointF &centrePos);
#endif

signals:
    void cellSizeChanged();
    void timerChanged();

#ifdef EXPOSE_VISUALISATION_API
    void nodeAddedToClosedList(const QPointF &centrePos);
    void nodeAddedToOpenList(const QPointF &centrePos);
    void nodeChosen(const QPointF &centrePos);
#endif
};

#endif // QUICKGRIDPATHER_H
