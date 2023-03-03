
#include "Transformation.h"
#include <QDebug>
#include <cmath>
#include <iostream>

Transform::Transform(QPoint rotCenter, int deg_angle)
    : m_rotCenter(rotCenter), m_angle(deg_angle * 3.14159 / 180)
{
}

QPointF Transform::operator()(QPointF point)
{
    float a_angle = atan2(point.y(), point.x()); // calculation angle
    float a_module = point.x() / cosf(a_angle);  // calculation module
    m_angle += a_angle;

    QPointF a_point{a_module * cos(m_angle) + m_rotCenter.x(), // calc new point
                    a_module * sin(m_angle) + m_rotCenter.y()};
    return a_point;
}