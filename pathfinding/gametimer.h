#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QDateTime>

#include "pathfinding_global.h"

class PATHFINDINGSHARED_EXPORT GameTimer : public QObject
{
    Q_OBJECT

public:
    GameTimer();

    Q_INVOKABLE void start(const QDateTime &gameStartDate = QDateTime());
    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void togglePaused();

    int fps() const;
    QDateTime dateTime() const;
    float timeSpeedMultiplier() const;
    void setTimeSpeedMultiplier(float timeSpeedMultiplier);

signals:
    void updated(float delta);

private slots:
    void doUpdate();

private:
    QDateTime dateFromSimulatedTime() const;

    void setRunning(bool running);

    bool mRunning;
    const int mFps;
    QTimer mTimer;
    QElapsedTimer mElapsedTimer;
    float mRemainder;
    /*! Seconds elapsed since this game was started; accumulates across saves. */
    double mSimulatedTime;
    float mTimeSpeedMultiplier;
    QDateTime mDateTime;
    QDateTime mGameStartDate;
};

#endif // GAMETIMER_H
