#include "gridpathagent.h"

#include "gridpathnode.h"
#include "utils.h"

GridPathAgent::GridPathAgent(const QPointF &targetPos) :
    mTargetPos(targetPos)
{
}

bool GridPathAgent::isPathComplete(const QuickEntity &entity, const QPointF &, const GridPathNode &currentNode) const
{
    return Utils::isNextToTargetPos(currentNode.pos(), mTargetPos, entity.speed());
}

int GridPathAgent::calculateStartCost(const GridPathNode &node) const
{
    QPointF distFromParent(Utils::abs(node.parent()->pos() - node.pos()));
    // The node's start cost will be its parent's plus the x and y distance from its parent.
    return node.parent()->startCost() + distFromParent.x() + distFromParent.y();
}

int GridPathAgent::calculateTargetCost(const GridPathNode &node) const
{
    QPointF distFromTarget(Utils::abs(mTargetPos - node.pos()));
    return distFromTarget.x() + distFromTarget.y();
}

void GridPathAgent::onPathComplete(QVector<QSharedPointer<GridPathNode> > &path)
{
    if (mExcludeFirstNode) {
        path.pop_front();
    }
}
