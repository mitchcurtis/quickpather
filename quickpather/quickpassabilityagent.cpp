#include "quickpassabilityagent.h"

namespace QuickPather {

QuickPassabilityAgent::QuickPassabilityAgent()
{
}

bool QuickPassabilityAgent::isPassable(const QPointF &, AbstractEntity *)
{
    return true;
}

}
