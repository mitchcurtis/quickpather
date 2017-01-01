#ifndef QUICKENTITY_H
#define QUICKENTITY_H

#include <QObject>

#include "quickpather_global.h"

class QQuickItem;

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT QuickEntity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit QuickEntity(QObject *parent = 0);
    ~QuickEntity();

    virtual QPointF centrePos() const;
    virtual void setCentrePos(const QPointF &centrePos);

    virtual qreal speed() const;
    virtual void setSpeed(qreal speed);

    virtual qreal rotation() const;
    virtual void setRotation(qreal rotation);

    QQuickItem *item() const;
    void setItem(QQuickItem *item);

signals:
    void entityDestroyed(QuickEntity *entity);
    void centrePosChanged();
    void speedChanged();
    void rotationChanged();
    void itemChanged();

private:
    QQuickItem *mItem;
    qreal mSpeed;
};

}

#endif // QUICKENTITY_H
