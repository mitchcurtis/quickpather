#ifndef GRIDPATHAGENT_H
#define GRIDPATHAGENT_H

#include <QPointF>

template <typename T>
class QVector;
template <typename T>
class QSharedPointer;

class GridPathNode;
class QuickEntity;

class GridPathAgent
{
public:
    GridPathAgent();

    virtual bool isPathComplete(const QuickEntity &entity, const QPointF &startPos, const GridPathNode &currentNode) const;
    virtual int calculateStartCost(const GridPathNode &node) const;
    virtual int calculateTargetCost(const GridPathNode &node) const;
    /*!
        Called when the path has been completed according to isPathComplete().

        Allows the agent to perform any optimisations on the path, if desired.
    */
    virtual void onPathComplete(QVector<QSharedPointer<GridPathNode> > &path);

    qreal mTargetLeniency;
    bool mExcludeFirstNode;
    const QuickEntity *mEntity;
    QPointF mTargetPos;
};

#endif // GRIDPATHAGENT_H
