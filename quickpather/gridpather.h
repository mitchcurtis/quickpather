#ifndef GRIDPATHER_H
#define GRIDPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

#include "gametimer.h"
#include "gridpathnode.h"
#include "passabilityagent.h"
#include "quickentity.h"
#include "steeringagent.h"

#define EXPOSE_VISUALISATION_API

namespace QuickPather {

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
    Q_PROPERTY(int cellSize READ cellSize WRITE setCellSize NOTIFY cellSizeChanged)
    Q_PROPERTY(QuickPather::GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)
    Q_PROPERTY(QuickPather::PassabilityAgent *passabilityAgent READ passabilityAgent WRITE setPassabilityAgent NOTIFY passabilityAgentChanged)
    Q_PROPERTY(QuickPather::SteeringAgent *steeringAgent READ steeringAgent WRITE setSteeringAgent NOTIFY steeringAgentChanged)

public:
    explicit GridPather(QObject *parent = nullptr);

    Q_INVOKABLE bool moveEntityTo(QuickPather::QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancelEntityMovement(QuickPather::QuickEntity *entity);

    int cellSize() const;
    void setCellSize(int cellSize);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

    GridPathData pathData(QuickEntity *entity) const;

    QuickPather::PassabilityAgent *passabilityAgent();
    void setPassabilityAgent(QuickPather::PassabilityAgent *passabilityAgent);

    QuickPather::SteeringAgent *steeringAgent();
    void setSteeringAgent(QuickPather::SteeringAgent *steeringAgent);

signals:
    void cellSizeChanged();
    void passabilityAgentChanged();
    void steeringAgentChanged();
    void timerChanged();

#ifdef EXPOSE_VISUALISATION_API
    void nodeAddedToClosedList(const QPointF &centrePos);
    void nodeAddedToOpenList(const QPointF &centrePos);
    void nodeChosen(const QPointF &centrePos);
#endif

protected:
    virtual void onCellSizeChanged(int oldCellSize, int newCellSize);

#ifdef EXPOSE_VISUALISATION_API
    virtual void onNodeAddedToClosedList(const QPointF &centrePos);
    virtual void onNodeAddedToOpenList(const QPointF &centrePos);
    virtual void onNodeChosen(const QPointF &centrePos);
#endif

private slots:
    void timerUpdated(qreal delta);

private:
    int mCellSize;
    GameTimer *mTimer;
    PassabilityAgent *mPassabilityAgent;
    SteeringAgent *mSteeringAgent;
    QHash<QuickEntity*, GridPathData> mData;
};

}

#endif // GRIDPATHER_H
