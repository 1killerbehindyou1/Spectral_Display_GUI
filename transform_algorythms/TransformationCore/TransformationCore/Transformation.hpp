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

class Transform
{

public:
    Transform(const QPointF& rotCenter, double deg_angle);

    QPointF operator()(const QPointF& point) const;

    QPolygonF operator()(const QRectF& rect) const;

private:
    QPointF m_rotCenter;
    double m_angle;
};
} // namespace common
