
#include "Transformation.h"
#include <QDebug>
#include <cmath>
#include <complex>
#include <iostream>

Transform::Transform(const QPointF& rotCenter, float deg_angle)
    : m_rotCenter(rotCenter), m_angle(deg_angle * 3.14159 / 180)
{
}

QPointF Transform::operator()(const QPointF& point)
{

    QPointF new_point = point - m_rotCenter;
    std::complex<float> new_point_cpl(new_point.x(), new_point.y());

    float angle = std::arg(new_point_cpl);
    if (new_point.y() < 0)
    {
        angle += 6.283;
    }
    float module = std::abs(new_point_cpl);
    m_angle += angle;
    QPointF out_point{module * cos(m_angle), module * sin(m_angle)};
    out_point += m_rotCenter;
    m_angle -= angle;
    return out_point;
}
