#ifndef HACKYPASSABILITYAGENT_H
#define HACKYPASSABILITYAGENT_H

#include "quickpassabilityagent.h"

class QQuickItem;

class HackyPassabilityAgent : public QuickPassabilityAgent
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *gridItem READ gridItem WRITE setGridItem NOTIFY gridItemChanged)

public:
    HackyPassabilityAgent();

    virtual bool isPassable(const QPointF &pos, AbstractEntity *entity);

    QQuickItem *gridItem() const;
    void setGridItem(QQuickItem *gridItem);

signals:
    void gridItemChanged();

private:
    QQuickItem *mGridItem;
};

#endif // HACKYPASSABILITYAGENT_H
