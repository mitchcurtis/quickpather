#include "gridpathnode.h"

namespace QuickPather {

GridPathNode::GridPathNode()
    : mStartCost(0)
    , mTargetCost(0)
{
}

GridPathNode::GridPathNode(const QPointF &pos)
    : mPos(pos)
    , mStartCost(0)
    , mTargetCost(0)
{
}

const QPointF& GridPathNode::pos() const
{
    return mPos;
}

QSharedPointer<GridPathNode> GridPathNode::parent()
{
    return mParent;
}

const QSharedPointer<GridPathNode> GridPathNode::parent() const
{
    return mParent;
}

void GridPathNode::setParent(QSharedPointer<GridPathNode> parent)
{
    mParent = parent;
}

int GridPathNode::startCost() const
{
    return mStartCost;
}

void GridPathNode::setStartCost(int cost)
{
    mStartCost = cost;
}

int GridPathNode::targetCost() const
{
    return mTargetCost;
}

void GridPathNode::setTargetCost(int cost)
{
    mTargetCost = cost;
}

int GridPathNode::totalCost() const
{
    return mStartCost + mTargetCost;
}

bool totalScoreLessThan(QSharedPointer<GridPathNode> lhs, QSharedPointer<GridPathNode> rhs)
{
    return lhs->totalCost() < rhs->totalCost();
}

}
