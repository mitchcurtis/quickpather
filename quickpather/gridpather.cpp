#include "gridpather.h"

#include <QDebug>
#include <QLoggingCategory>
#include <QQuickItem>

#include "entity.h"
#include "gametimer.h"
#include "gridpathagent.h"
#include "steeringagent.h"
#include "utils.h"

Q_LOGGING_CATEGORY(lcGridPather, "quickpather.gridpather")

GridPathData::GridPathData() :
    mCurrentNodeIndex(-1)
{
}

bool GridPathData::isValid() const
{
    return mCurrentNodeIndex != -1;
}

QPointF GridPathData::targetPos() const
{
    return mTargetPos;
}

QVector<QSharedPointer<GridPathNode> > GridPathData::nodes() const
{
    return mNodes;
}

int GridPathData::currentNodeIndex() const
{
    return mCurrentNodeIndex;
}

GridPather::GridPather(QObject *parent) :
    QObject(parent),
    mCellSize(32),
    mTimer(nullptr),
    mSteeringAgent(new SteeringAgent(this))
{
}

// TODO: abstract class
static bool isPassable(const QPointF &pos, AbstractEntity *entity)
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

/*
   Moves \a entity to \a pos.

   If a path to \a pos was found, any existing movement instructions are removed.
*/
bool GridPather::moveEntityTo(AbstractEntity *entity, const QPointF &pos)
{
    if (!mTimer) {
        qWarning() << "No timer set";
        return false;
    }

    const QPointF startPos = entity->centrePos();
    if (!isPassable(startPos, entity)) {
        qCDebug(lcGridPather) << "Starting position" << pos << "isn't passable for" << entity;
        return false;
    }

    // TODO: ensure target ends up precisely over node
    if (fmod(startPos.x() - mCellSize / 2, mCellSize) != 0 || fmod(startPos.y() - mCellSize / 2, mCellSize) != 0) {
        qDebug() << fmod(startPos.x(), mCellSize) << fmod(startPos.y(), mCellSize);
        qWarning() << "Currently incapable of dealing with non-cell-centered positions";
        return false;
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
        return false;
    }

    if(closedList.empty()) {
        qCDebug(lcGridPather) << "Impossible for" << entity << "to reach target pos" << pos;
        return false;
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
    pathData.mTargetPos = pos;
    pathData.mNodes = shortestPath;
    pathData.mCurrentNodeIndex = 0;
    mData.insert(entity, pathData);

    qCDebug(lcGridPather) << "Successfully found path (" << shortestPath.size() << "nodes) for" << entity << "to target pos" << pos;
    return true;
}

void GridPather::cancelEntityMovement(AbstractEntity *entity)
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

    const int oldCellSize = mCellSize;
    mCellSize = cellSize;
    onCellSizeChanged(oldCellSize, mCellSize);
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

    GameTimer *oldTimer = mTimer;
    mTimer = timer;
    onTimerChanged(oldTimer, mTimer);

    if (mTimer)
        connect(mTimer, &GameTimer::updated, this, &GridPather::timerUpdated);
}

GridPathData GridPather::pathData(AbstractEntity *entity) const
{
    GridPathData data;

    auto dataIt = mData.constFind(entity);
    if (dataIt != mData.constEnd()) {
        data = *dataIt;
    }

    return data;
}

void GridPather::onNodeAddedToClosedList(const QPointF &)
{
}

void GridPather::onNodeAddedToOpenList(const QPointF &)
{
}

void GridPather::onNodeChosen(const QPointF &)
{
}

void GridPather::onCellSizeChanged(int, int)
{
}

void GridPather::onTimerChanged(GameTimer *, GameTimer *)
{
}

void GridPather::timerUpdated(qreal delta)
{
    QHashIterator<AbstractEntity*, GridPathData> it(mData);
    while (it.hasNext()) {
        it.next();
        AbstractEntity *entity = it.key();

        GridPathData &pathData = mData[entity];
        if (pathData.mCurrentNodeIndex < pathData.mNodes.size()) {
            const GridPathNode currentNode = *pathData.mNodes.at(pathData.mCurrentNodeIndex);
            if (mSteeringAgent->steerTo(entity, currentNode.pos(), delta)) {
                // We've reached the current node.
                ++pathData.mCurrentNodeIndex;
            }
        } else {
            mData.remove(entity);
        }
    }
}
