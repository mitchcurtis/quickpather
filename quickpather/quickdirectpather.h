#ifndef QUICKDIRECTPATHER_H
#define QUICKDIRECTPATHER_H

#include "quickpather_global.h"

#include <QHash>
#include <QObject>
#include <QPointF>
#include <QVector>

namespace QuickPather {

class GameTimer;
class SteeringAgent;
class QuickEntity;

class DirectPathData
{
public:
    QPointF targetPos;
};

class QUICKPATHERSHARED_EXPORT QuickDirectPather : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QuickPather::GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    explicit QuickDirectPather(QObject *parent = nullptr);

    Q_INVOKABLE void moveEntityTo(QuickPather::QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancelEntityMovement(QuickPather::QuickEntity *entity);

    GameTimer *timer() const;
    void setTimer(GameTimer *timer);

signals:
    void timerChanged();

private slots:
    void timerUpdated(qreal delta);

private:
    GameTimer *mTimer;
    SteeringAgent *mSteeringAgent;
    QHash<QuickEntity*, DirectPathData> mData;
};

}

#endif // QUICKDIRECTPATHER_H
