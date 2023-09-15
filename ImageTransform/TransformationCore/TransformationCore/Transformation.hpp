#pragma once

#include "ColorCalc.hpp"
#include "Constants.hpp"
#include <QPoint>
#include <QPointF>
#include <QPolygon>
#include <QPolygonF>
#include <QRect>
#include <QRectF>
#include <cmath>
#include <complex>
#include <iostream>

namespace common
{

template <typename T_angle, typename T_point, typename T_quadrangle>
class Transform
{

public:
    Transform(const T_point& rotCenter, T_angle deg_angle)
        : m_rotCenter{rotCenter}, m_angle{deg_angle}
    {
    }

    QPointF operator()(const T_point& point) const
    {
        QPointF point_f{point};
        QPointF new_point = point_f - m_rotCenter;
        std::complex<double> new_point_cpl(new_point.x(), new_point.y());

        double angle = std::arg(new_point_cpl);

        angle += new_point.y() < 0 ? constants::two_pi : 0;

        double module = std::abs(new_point_cpl);
        angle += m_angle;

        QPointF out_point{module * cos(m_angle), module * sin(m_angle)};
        out_point += m_rotCenter;

        return out_point;
    }

    QPolygonF operator()(const T_quadrangle& rect)
    {
        QPolygonF result;
        QPolygonF polygon{rect};

        for (const QPointF& p : polygon)
        {
            result << Transform::operator()(p);
        }
        return result;
    };

private:
    QPointF m_rotCenter;
    double m_angle;
};

using Transform_float = common::Transform<double, QPointF, QPolygonF>;

}; // namespace common
