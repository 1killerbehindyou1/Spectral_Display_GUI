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

template <typename T_angle, typename T_point, typename T_rect, typename T_poly>
class Transform
{

public:
    Transform(const T_point& rotCenter, T_angle deg_angle)
        : m_rotCenter{rotCenter}, m_angle{deg_angle}
    {
    }

    T_point operator()(const T_point& point) const
    {
        T_point new_point = point - m_rotCenter;
        std::complex<T_angle> new_point_cpl(new_point.x(), new_point.y());

        T_angle angle = std::arg(new_point_cpl);

        angle += new_point.y() < 0 ? constants::two_pi : 0;

        T_angle module = std::abs(new_point_cpl);
        angle += m_angle;

        T_point out_point{module * cos(m_angle), module * sin(m_angle)};
        out_point += m_rotCenter;

        return out_point;
    }

    T_rect operator()(const T_rect& rect)
    {
        T_point top_left = this->operator()(rect.topLeft());
        T_point bottom_right = this->operator()(rect.bottomRight());
        return {top_left.toPoint(), bottom_right.toPoint()};
    };

    T_poly operator()(const T_poly& poly)
    {
        T_poly result;
        for (const T_point& p : poly)
        {
            result << Transform::operator()(p);
        }
        return result;
    }

private:
    T_point m_rotCenter;
    T_angle m_angle;
};

using Transform_float = common::Transform<float, QPointF, QRectF, QPolygonF>;
using Transform_int = common::Transform<int, QPoint, QRect, QPolygon>;

}; // namespace common
