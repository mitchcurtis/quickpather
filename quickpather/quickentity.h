#ifndef QUICKENTITY_H
#define QUICKENTITY_H

#include <QObject>

#include "quickpather_global.h"

class QQuickItem;

class QUICKPATHERSHARED_EXPORT QuickEntity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit QuickEntity(QObject *parent = 0);

    QQuickItem *item() const;
    void setItem(QQuickItem *item);

    qreal speed() const;
    void setSpeed(const qreal &speed);

signals:
    void itemChanged();
    void speedChanged();

public slots:

private:
    QQuickItem *mItem;
    qreal mSpeed;
};

#endif // QUICKENTITY_H
