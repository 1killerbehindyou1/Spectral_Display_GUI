#pragma once

#include "ColorCalc.hpp"
#include "Constants.hpp"
#include <QPointF>
#include <QPolygonF>
#include <QRectF>
#include <cmath>
#include <complex>
#include <iostream>

namespace common
{

/**
 * @brief 2D rotation transform around selected center.
 */
class Transform
{

public:
    /**
     * @brief Creates rotation transform.
     * @param rotCenter Rotation center.
     * @param deg_angle Rotation angle in degrees.
     */
    Transform(const QPointF& rotCenter, double deg_angle);
    /**
     * @brief Applies transform to point.
     * @param point Input point.
     * @return Rotated point.
     */
    QPointF operator()(const QPointF& point) const;
    /**
     * @brief Applies transform to rectangle corners.
     * @param rect Input rectangle.
     * @return Polygon of transformed rectangle corners.
     */
    QPolygonF operator()(const QRectF& rect) const;

private:
    /** @brief Rotation center in source coordinate space. */
    QPointF m_rotCenter;
    /** @brief Rotation angle in radians. */
    double m_angle;
};
} // namespace common
