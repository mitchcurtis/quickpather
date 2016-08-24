#ifndef QUICKPASSABILITYAGENT_H
#define QUICKPASSABILITYAGENT_H

#include <QObject>

#include "abstractpassabilityagent.h"

class QUICKPATHERSHARED_EXPORT QuickPassabilityAgent : public QObject, public AbstractPassabilityAgent
{
    Q_OBJECT

public:
    QuickPassabilityAgent();

    virtual bool isPassable(const QPointF &pos, AbstractEntity *entity);
};

#endif // QUICKPASSABILITYAGENT_H
