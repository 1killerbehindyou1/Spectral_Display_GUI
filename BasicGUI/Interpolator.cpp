
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

QVector<QPointF> Interpolator::interpolatorTransform(QPoint center_of_rot,
                                                     QRect rect,
                                                     float deg_angle)
{
    QVector<QPointF> vector_points;
    QPointF curr_point;

    for (int y = 0; y < rect.height(); y++)
    {
        curr_point.setY(rect.topLeft().y() + y);

        for (int x = 0; x < rect.width(); x++)
        {
            curr_point.setX(rect.topLeft().x() + x);

            Transform trans(center_of_rot, deg_angle);
            vector_points.push_front(trans(curr_point));
        }
    }
    return vector_points;
}