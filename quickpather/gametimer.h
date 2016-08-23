#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QDateTime>

#include "quickpather_global.h"

class QUICKPATHERSHARED_EXPORT GameTimer : public QObject
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
    qreal timeSpeedMultiplier() const;
    void setTimeSpeedMultiplier(qreal timeSpeedMultiplier);

signals:
    void updated(qreal delta);

private slots:
    void doUpdate();

private:
    QDateTime dateFromSimulatedTime() const;

    void setRunning(bool running);

    bool mRunning;
    const int mFps;
    QTimer mTimer;
    QElapsedTimer mElapsedTimer;
    qreal mRemainder;
    /*! Seconds elapsed since this game was started; accumulates across saves. */
    double mSimulatedTime;
    qreal mTimeSpeedMultiplier;
    QDateTime mDateTime;
    QDateTime mGameStartDate;
};

#endif // GAMETIMER_H
