#ifndef GRIDPATHER_H
#define GRIDPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

#include "gridpathnode.h"

namespace QuickPather {

class AbstractEntity;
class AbstractPassabilityAgent;
class GameTimer;
class SteeringAgent;

class QUICKPATHERSHARED_EXPORT GridPathData
{
public:
    GridPathData();

    bool isValid() const;

    QPointF targetPos() const;
    QVector<QSharedPointer<GridPathNode> > nodes() const;
    int currentNodeIndex() const;
private:
    friend class GridPather;

    QPointF mTargetPos;
    QVector<QSharedPointer<GridPathNode> > mNodes;
    int mCurrentNodeIndex;
};

class QUICKPATHERSHARED_EXPORT GridPather : public QObject
{
    Q_OBJECT

public:
    explicit GridPather(QObject *parent = nullptr);

    bool moveEntityTo(AbstractEntity *entity, const QPointF &pos);
    void cancelEntityMovement(AbstractEntity *entity);

    int cellSize() const;
    void setCellSize(int cellSize);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

    GridPathData pathData(AbstractEntity *entity) const;

protected:
    virtual void onCellSizeChanged(int oldCellSize, int newCellSize);
    virtual void onTimerChanged(GameTimer *oldTimer, GameTimer *newTimer);
    virtual void onPassabilityAgentChanged(AbstractPassabilityAgent *oldAgent, AbstractPassabilityAgent *newAgent);

    virtual void onNodeAddedToClosedList(const QPointF &centrePos);
    virtual void onNodeAddedToOpenList(const QPointF &centrePos);
    virtual void onNodeChosen(const QPointF &centrePos);

    AbstractPassabilityAgent *passabilityAgent();
    void setPassabilityAgent(AbstractPassabilityAgent *passabilityAgent);

private slots:
    void timerUpdated(qreal delta);

private:
    int mCellSize;
    GameTimer *mTimer;
    SteeringAgent *mSteeringAgent;
    AbstractPassabilityAgent *mPassabilityAgent;
    QHash<AbstractEntity*, GridPathData> mData;
};

}

#endif // GRIDPATHER_H
