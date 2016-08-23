#ifndef UTILS_H
#define UTILS_H

#include <QtMath>
#include <QPointF>
#include <QTransform>
#include <QQuickItem>

#include "quickentity.h"

namespace Utils {
    inline bool fuzzyCompare(const QPointF &lhs, const QPointF &rhs, qreal fuzz = 0.0001) {
        return qAbs(lhs.x() - rhs.x()) <= fuzz && qAbs(lhs.y() - rhs.y()) <= fuzz;
    }

    inline qreal clampAngle(qreal angle)
    {
        angle = fmod(angle, 360.0f);
        if(angle < 0)
            angle += 360.0f;
        return angle;
    }

    inline QPointF centrePosition(const QQuickItem *item)
    {
        return item->position() + QPointF(item->width() / 2.0, item->height() / 2.0);
    }

    inline qreal directionTo(const QPointF &source, const QPointF &target) {
        QPointF toTarget(target.x() - source.x(), target.y() - source.y());
        qreal facingTarget = Utils::clampAngle(qRadiansToDegrees(atan2(toTarget.y(), toTarget.x())));
        return facingTarget;
    }

    inline qreal cartesianDirectionTo(const QPointF &source, const QPointF &target) {
        QPointF toTarget(target.x() - source.x(), target.y() - source.y());
        qreal facingTarget = Utils::clampAngle(qRadiansToDegrees(atan2(toTarget.y() * -1, toTarget.x())));
        return facingTarget;
    }

    inline QPointF moveBy(const QPointF &pos, qreal rotation, qreal distance)
    {
        return pos - QTransform().rotate(rotation).map(QPointF(0, distance));
    }

    inline QPointF abs(const QPointF &point) {
        return QPoint(::abs(point.x()), ::abs(point.y()));
    }

    inline bool isNextToTargetPos(QuickEntity *entity, const QPointF &targetPos, qreal targetLeniency = -1)
    {
        if (targetLeniency == -1)
            targetLeniency = qMax(1.0, entity->speed() * 0.05);
        return Utils::fuzzyCompare(Utils::centrePosition(entity->item()), targetPos, targetLeniency);
    }

    inline bool isNextToTargetPos(const QPointF &entityCentrePos, const QPointF &targetPos, qreal entitySpeed, qreal targetLeniency = -1)
    {
        if (targetLeniency == -1)
            targetLeniency = qMax(1.0, entitySpeed * 0.05);
        return Utils::fuzzyCompare(entityCentrePos, targetPos, targetLeniency);
    }
}

#endif // UTILS_H
