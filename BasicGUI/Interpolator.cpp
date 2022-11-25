
#include "Interpolator.h"
#include <QDebug>
#include <cmath>
#include <iostream>
//////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////
Interpolator::Interpolator(QObject* parent) : QObject(parent) {}
// class Transform;

QColor Interpolator::interpolatorSetLedColor(QVector<QPointF> vector_points)
{
    QImage image = inerpolator_pixmap.toImage();
    QColor color;

    red_component.sum = 0;
    green_component.sum = 0;
    blue_component.sum = 0;
    red_component.level = 0;
    green_component.level = 0;
    blue_component.level = 0;

    for (QPointF point : vector_points)
    {

        color = image.pixelColor(static_cast<int>(point.x()),
                                 static_cast<int>(point.y()));

        red_component.sum += color.red();
        green_component.sum += color.green();
        blue_component.sum += color.blue();
    }

    int rect_size = vector_points.size();

    if (rect_size > 0)
    {
        red_component.level = red_component.sum / rect_size;
        green_component.level = green_component.sum / rect_size;
        blue_component.level = blue_component.sum / rect_size;
    }

    return color = color.fromRgb(red_component.level, green_component.level,
                                 blue_component.level);
}
/**
 *      @brief Function Interpolator::interpolatorTransform
 *       creates a vector points, which are contained in actually checked
 *       rectangle
 */

QVector<QPointF> Interpolator::interpolatorTransform(QPoint center_of_rot,
                                                     QRect rect,
                                                     float deg_angle)
{
    QVector<QPointF> vector_points;
    QPointF rect_top_left = rect.topLeft();
    PointInReferenceSystem current_point;
    float ext_angle = Transform::convertAngleToRad(deg_angle);

    for (int yy = 0; yy < rect.height(); yy++)
    {
        current_point.point.setY(rect_top_left.y() + yy);

        for (int xx = 0; xx < rect.width(); xx++)
        {
            current_point.point.setX(rect_top_left.x() + xx);
            current_point.angle = Transform::calcAngle(current_point.point);
            current_point.module =
                Transform::calcModule(current_point.point, current_point.angle);
            current_point.angle =
                Transform::updateAngle(ext_angle, current_point.angle);
            current_point.point = Transform::updatePoint(
                center_of_rot, current_point.point, current_point.module,
                current_point.angle);
            vector_points.push_front(current_point.point);

            current_point.angle = 0;
            current_point.point.setY(rect_top_left.y() + yy);
            current_point.point.setX(rect_top_left.x() + xx);
        }
    }
    return vector_points;
}
