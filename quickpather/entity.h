#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QPointF>

#include "abstractentity.h"

namespace QuickPather {

class QUICKPATHERSHARED_EXPORT Entity : public QObject, public AbstractEntity
{
    Q_OBJECT
    Q_PROPERTY(QPointF centrePos READ centrePos WRITE setCentrePos NOTIFY centrePosChanged)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)

public:
    explicit Entity(QObject *parent = 0);

    virtual QPointF centrePos() const override;
    virtual void setCentrePos(const QPointF &centrePos) override;

    virtual qreal speed() const override;
    virtual void setSpeed(qreal speed) override;

    virtual qreal rotation() const override;
    virtual void setRotation(qreal rotation) override;

signals:
    void centrePosChanged();
    void speedChanged();
    void rotationChanged();

public slots:

private:
    QPointF mCentrePos;
    qreal mSpeed;
    qreal mRotation;
};

}

#endif // ENTITY_H
