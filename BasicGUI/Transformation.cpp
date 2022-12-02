
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
float Transform::updateAngle(float ext_angle, float angle)
{
    return angle + ext_angle;
}
QPointF Transform::updatePoint(QPointF center_of_rot, QPointF point,
                               float module, float angle)
{
    point.setX(module * cos(angle) + center_of_rot.x());
    point.setY(module * sin(angle) + center_of_rot.y());
    return point;
}
