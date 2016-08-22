#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <QtMath>
#include <QPointF>

namespace MathUtils {
    inline bool fuzzyCompare(const QPointF &lhs, const QPointF &rhs, qreal fuzz = 0.0001) {
        return qAbs(lhs.x() - rhs.x()) <= fuzz && qAbs(lhs.y() - rhs.y()) <= fuzz;
    }

    inline float clampAngle(float angle)
    {
        angle = fmod(angle, 360.0f);
        if(angle < 0)
            angle += 360.0f;
        return angle;
    }
}

#endif // MATHUTILS_H
