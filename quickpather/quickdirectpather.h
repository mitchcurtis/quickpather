#ifndef QUICKDIRECTPATHER_H
#define QUICKDIRECTPATHER_H

#include "directpather.h"

class QuickEntity;

class QUICKPATHERSHARED_EXPORT QuickDirectPather : public DirectPather
{
    Q_OBJECT
    Q_PROPERTY(GameTimer *timer READ timer WRITE setTimer NOTIFY timerChanged)

public:
    explicit QuickDirectPather(QObject *parent = 0);

    Q_INVOKABLE void moveTo(QuickEntity *entity, const QPointF &pos);
    Q_INVOKABLE void cancel(QuickEntity *entity);

protected:
    virtual void onTimerChanged(GameTimer *oldTimer, GameTimer *newTimer) override;

signals:
    void timerChanged();
};


#endif // QUICKDIRECTPATHER_H
