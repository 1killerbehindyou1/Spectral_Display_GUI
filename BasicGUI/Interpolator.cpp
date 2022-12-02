
#include "Interpolator.h"
#include "Transformation.h"
#include <QDebug>
#include <cmath>
#include <iostream>

//////////////////////////////////////////////////////////////////
Interpolator::Interpolator(QObject* parent) : QObject(parent) {}

//////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////
QVector<QPointF> Interpolator::interpolatorTransform(QPoint a_center_of_rot,
                                                     QRect a_rect,
                                                     float a_deg_angle)
{
    QVector<QPointF> vector_points;

    QPointF t_rect_top_left = a_rect.topLeft();

    QPointF t_current_point;
    float t_module = 0;
    float t_angle = 0;

    float t_ext_angle = Transform::convertAngleToRad(a_deg_angle);

    for (int yy = 0; yy < a_rect.height(); yy++)
    {
        t_current_point.setY(t_rect_top_left.y() + yy);

        for (int xx = 0; xx < a_rect.width(); xx++)
        {
            t_current_point.setX(t_rect_top_left.x() + xx);
            t_angle = Transform::calcAngle(t_current_point);
            t_module = Transform::calcModule(t_current_point, t_angle);
            t_angle = Transform::updateAngle(t_ext_angle, t_angle);
            t_current_point = Transform::updatePoint(
                a_center_of_rot, t_current_point, t_module, t_angle);
            vector_points.push_front(t_current_point);

            t_angle = 0;
            t_current_point.setY(t_rect_top_left.y() + yy);
            t_current_point.setX(t_rect_top_left.x() + xx);
        }
    }
    return vector_points;
}
