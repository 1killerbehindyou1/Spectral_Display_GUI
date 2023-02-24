
#include "Transformation.h"
#include <QDebug>
#include <cmath>
#include <iostream>

Transform::Transform(QPoint rotCenter, int deg_angle) : m_rotCenter(rotCenter)
{
    m_angle = convertAngleToRad(deg_angle);
}

QPointF Transform::operator()(QPointF point)
{
    float a_angle = calcAngle(point);
    float a_module = calcModule(point, a_angle);
    m_angle += a_angle;
    QPointF a_point = transformPoint(m_rotCenter, a_module, m_angle);

    return a_point;
}
////////////////////////////////////////////////////////////////////////////
namespace
{

float calcModule(QPointF point, float angle) { return point.x() / cosf(angle); }

float calcAngle(QPointF point) { return atan2(point.y(), point.x()); }

float convertAngleToRad(int deg_angle) { return deg_angle * 3.14159 / 180; }

QPointF transformPoint(QPointF rotCenter, float module, float angle)
{
    return fromPolar(module, angle) + rotCenter;
}

QPointF fromPolar(float module, float angle)
{
    return {module * cos(angle), module * sin(angle)};
}
} // namespace
