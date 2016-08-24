#include "gridpather.h"

#include <QDebug>
#include <QLoggingCategory>
#include <QQuickItem>

#include "gametimer.h"
#include "gridpathagent.h"
#include "quickentity.h"
#include "steeringagent.h"
#include "utils.h"

Q_LOGGING_CATEGORY(lcGridPather, "quickpather.gridpather")

GridPather::GridPather() :
    mCellSize(32),
    mTimer(nullptr),
    mSteeringAgent(new SteeringAgent(this))
{
}

// TODO: abstract class
static bool isPassable(const QPointF &pos, QuickEntity *entity)
{
    Q_UNUSED(pos);
    Q_UNUSED(entity);
    return true;
}

static int iterationLimit = 1000;

static const QPointF north(0, -1);
static const QPointF south(0, 1);
static const QPointF east(1, 0);
static const QPointF west(-1, 0);

static const qreal northRotation = 0;
static const qreal southRotation = 180;
static const qreal eastRotation = 90;
static const qreal westRotation = 270;

static const int qtyStraightDirections = 4;

const QPointF straightDirections[qtyStraightDirections] = {
    north, south, east, west
};

void GridPather::moveTo(QuickEntity *entity, const QPointF &pos)
{
    if (!mTimer) {
        qWarning() << "No timer set";
        return;
    }

    const QPointF startPos = Utils::centrePosition(entity->item());
    if (!isPassable(startPos, entity)) {
        qCDebug(lcGridPather) << "Starting position" << pos << "isn't passable for" << entity->item();
        return;
    }

    QVector<QSharedPointer<GridPathNode> > openList;
    QVector<QSharedPointer<GridPathNode> > closedList;
    QVector<QSharedPointer<GridPathNode> > shortestPath;

    // Starting square is automatically in the open list.
    QSharedPointer<GridPathNode> startNode(new GridPathNode(startPos));
    openList.push_back(startNode);

    // The selected node is the last selected node that was put on the closed list.
    QSharedPointer<GridPathNode> selectedNode;
    int iterations = 0;
    const QPointF nodeDist(mCellSize, mCellSize);
//    const QPointF boundsEnlargement = characterBoundsEnlargement();

    GridPathAgent pathAgent(pos);

    typedef QVector<QSharedPointer<GridPathNode> > NodeVector;
    typedef NodeVector::iterator node_it;
    typedef NodeVector::const_iterator const_node_it;

    do {
        // Look for the lowest "total cost" square on the open list. We refer to this as the selected node.
        node_it lowest = std::min_element(openList.begin(), openList.end(), totalScoreLessThan);
        // Switch it to the closed list.
        closedList.push_back(*lowest);
#ifdef EXPOSE_VISUALISATION_API
        emit nodeAddedToClosedList((*lowest)->pos());
#endif
        selectedNode = *lowest;
        openList.erase(lowest);

        // The search is finished when ...
        if (pathAgent.isPathComplete(*entity, startPos, *selectedNode)) {
            break;
        }

        // For each of the 4 squares adjacent to this current square...
        for(int dirIndex = 0; dirIndex < qtyStraightDirections; ++dirIndex) {
            // Centre of the node.
            const QPointF nodePos(selectedNode->pos() + straightDirections[dirIndex] * nodeDist.x());

            QSharedPointer<GridPathNode> adjNode(new GridPathNode(nodePos));

            bool walkable = isPassable(adjNode->pos(), entity/*, &boundsEnlargement*/);
            bool isOnClosedList = std::find_if(closedList.begin(), closedList.end(),
                PathNodePosComp(adjNode)) != closedList.end();

            if(walkable && !isOnClosedList) {
                node_it onOpenList = std::find_if(openList.begin(), openList.end(), PathNodePosComp(adjNode));
                bool isOnOpenList = onOpenList != openList.end();

                if(isOnOpenList) {
                    // Check to see if this path to adj_node is better, using "start cost" as the measure.
                    QSharedPointer<GridPathNode> nodeCopy(new GridPathNode(*(*onOpenList)));

                    nodeCopy->setParent(selectedNode);
                    nodeCopy->setStartCost(pathAgent.calculateStartCost(*nodeCopy));
                    nodeCopy->setTargetCost(pathAgent.calculateTargetCost(*nodeCopy));

                    if((*onOpenList)->startCost() < nodeCopy->startCost()) {
                        // Is improved; change its parent to selected.
                        adjNode->setParent(selectedNode);
                        adjNode->setStartCost(pathAgent.calculateStartCost(*adjNode));
                        adjNode->setTargetCost(pathAgent.calculateTargetCost(*adjNode));
                    }
                } else {
                    // Not on open list; add it.
                    adjNode->setParent(selectedNode);
                    adjNode->setStartCost(pathAgent.calculateStartCost(*adjNode));
                    adjNode->setTargetCost(pathAgent.calculateTargetCost(*adjNode));

                    openList.push_back(adjNode);
#ifdef EXPOSE_VISUALISATION_API
                    emit nodeAddedToOpenList(adjNode->pos());
#endif
                }
            }
        }

        ++iterations;
    } while(iterations < iterationLimit && !openList.empty());

    if (iterations == iterationLimit) {
        qWarning() << "iteration limit (" << iterationLimit << ") reached.";
        return;
    }

    if(closedList.empty()) {
        qCDebug(lcGridPather) << "Impossible for" << entity->item() << "to reach target pos" << pos;
        return;
    }

    // To get the actual shortest path: working backwards from the target square,
    // we go from each node to its parent node until we reach the starting node.
    QSharedPointer<GridPathNode> node = closedList.back();
    QVector<QSharedPointer<GridPathNode> > test;
    while(node) {
#ifdef EXPOSE_VISUALISATION_API
        emit nodeChosen(node->pos());
#endif

        shortestPath.push_front(node);
        test.insert(test.begin(), node);
        node = node->parent();
    }

    if(!shortestPath.isEmpty()) {
        shortestPath.pop_front();
    }

    GridPathData pathData;
    pathData.targetPos = pos;
    pathData.nodes = shortestPath;
    pathData.currentNodeIndex = 0;
    mData.insert(entity, pathData);

    qCDebug(lcGridPather) << "Successfully found path (" << shortestPath.size() << "nodes) for" << entity->item() << "to target pos" << pos;
}

void GridPather::cancel(QuickEntity *entity)
{
    mData.remove(entity);
}

int GridPather::cellSize() const
{
    return mCellSize;
}

void GridPather::setCellSize(int cellSize)
{
    if (!mData.isEmpty()) {
        qWarning() << "Cannot set cell size while pathing active";
        return;
    }

    if (cellSize == mCellSize)
        return;

    mCellSize = cellSize;
    emit cellSizeChanged();
}

GameTimer *GridPather::timer() const
{
    return mTimer;
}

void GridPather::setTimer(GameTimer *timer)
{
    if (timer == mTimer)
        return;

    if (mTimer)
        mTimer->disconnect(this);

    mTimer = timer;

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &GridPather::timerUpdated);

    emit timerChanged();
}

void GridPather::timerUpdated(qreal delta)
{
    QHashIterator<QuickEntity*, GridPathData> it(mData);
    while (it.hasNext()) {
        it.next();
        QuickEntity *entity = it.key();

        GridPathData &pathData = mData[entity];
        if (pathData.currentNodeIndex < pathData.nodes.size()) {
            const GridPathNode currentNode = *pathData.nodes.at(pathData.currentNodeIndex);
            if (mSteeringAgent->steerTo(entity, currentNode.pos(), delta)) {
                // We've reached the current node.
                ++pathData.currentNodeIndex;
            }
        } else {
            mData.remove(entity);
        }
    }
}
