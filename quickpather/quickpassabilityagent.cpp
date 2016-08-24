#include "quickpassabilityagent.h"

QuickPassabilityAgent::QuickPassabilityAgent()
{
}

bool QuickPassabilityAgent::isPassable(const QPointF &, AbstractEntity *)
{
    return true;
}
