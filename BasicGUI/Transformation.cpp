
#include "Transformation.h"
#include <QDebug>
#include <cmath>
#include <iostream>

float Transform::calcModule(QPointF point, float angle)
{
    float module = point.x() / cosf(angle);
    return module;
}

float Transform::calcAngle(QPointF point)
{
    float angle = atan2(point.y(), point.x());
    return angle;
}

float Transform::convertAngleToRad(float deg_angle)
{
    float ext_angle;
    return ext_angle * 3.14159 / 180;
}

QPointF Transform::transformPoint(QPointF rotCenter, QPointF point,
                                  float module, float angle)
{
    point.setX(module * cos(angle) + rotCenter.x());
    point.setY(module * sin(angle) + rotCenter.y());
    return point;
}

Transform::Transform(QPoint rotCenter, float deg_angle) : m_rotCenter(rotCenter)

{
    m_angle = convertAngleToRad(deg_angle);
}

QPointF Transform::transformFrom(QPointF point)
{

    float a_angle = Transform::calcAngle(point);
    float a_module = Transform::calcModule(point, a_angle);
    m_angle += a_angle;
    QPointF a_point = transformPoint(m_rotCenter, point, a_module, m_angle);

    return a_point;
}
