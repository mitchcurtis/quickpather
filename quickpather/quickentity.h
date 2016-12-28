#ifndef QUICKENTITY_H
#define QUICKENTITY_H

#include <QObject>

#include "abstractentity.h"
#include "quickpather_global.h"

class QQuickItem;

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT QuickEntity : public QObject, public AbstractEntity
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    explicit QuickEntity(QObject *parent = 0);

    virtual QPointF centrePos() const override;
    virtual void setCentrePos(const QPointF &centrePos) override;

    virtual qreal speed() const override;
    virtual void setSpeed(qreal speed) override;

    virtual qreal rotation() const override;
    virtual void setRotation(qreal rotation) override;

    QQuickItem *item() const;
    void setItem(QQuickItem *item);

signals:
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
