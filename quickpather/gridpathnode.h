#ifndef GRIDPATHNODE_H
#define GRIDPATHNODE_H

#include <QJsonObject>
#include <QPointF>
#include <QSharedPointer>

#include "quickpather_global.h"

class QUICKPATHERSHARED_EXPORT GridPathNode
{
public:
    GridPathNode();
    GridPathNode(const QPointF& pos);

    const QPointF &pos() const;

    QSharedPointer<GridPathNode> parent();
    const QSharedPointer<GridPathNode> parent() const;
    void setParent(QSharedPointer<GridPathNode> parent);

    int startCost() const;
    void setStartCost(int cost);
    int targetCost() const;
    void setTargetCost(int cost);

    int totalCost() const;

private:
    QSharedPointer<GridPathNode> mParent;
    QPointF mPos;
    // The cost of travelling from the start node to this node.
    int mStartCost;
    // The cost of travelling from the target node to this node.
    int mTargetCost;
};

class PathNodePosComp
{
public:
    PathNodePosComp(QSharedPointer<GridPathNode> toComp)
    : mToComp(toComp)
    {
    }

    bool operator()(QSharedPointer<GridPathNode> node)
    {
        return mToComp->pos() == node->pos();
    }
private:
    QSharedPointer<GridPathNode> mToComp;
};

bool totalScoreLessThan(QSharedPointer<GridPathNode> lhs, QSharedPointer<GridPathNode> rhs);

#endif // GRIDPATHNODE_H
