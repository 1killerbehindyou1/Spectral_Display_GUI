
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
    QPointF a_point = transformPoint(m_rotCenter, point, a_module, m_angle);

    return a_point;
}

////////////////////////////////////////////////////////////////////////////
namespace
{

float calcModule(QPointF point, float angle)
{
    float module = point.x() / cosf(angle);
    return module;
}

float calcAngle(QPointF point)
{
    float angle = atan2(point.y(), point.x());
    return angle;
}

float convertAngleToRad(int deg_angle)
{
    float ext_angle;
    return ext_angle * 3.14159 / 180;
}

QPointF transformPoint(QPointF rotCenter, QPointF point, float module,
                       float angle)
{
    point.setX(module * cos(angle) + rotCenter.x());
    point.setY(module * sin(angle) + rotCenter.y());
    return point;
}
} // namespace
