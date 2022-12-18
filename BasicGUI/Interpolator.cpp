
#include "Interpolator.h"
#include <QDebug>
#include <cmath>
#include <iostream>

//////////////////////////////////////////////////////////////////
Interpolator::Interpolator(QObject* parent) : QObject(parent) {}

//////////////////////////////////////////////////////////////////
QColor Interpolator::interpolatorSetLedColor(QVector<QPointF> vector_points)
{
    QImage image{};
    if (inerpolator_pixmap != nullptr)
        image = inerpolator_pixmap->toImage();

    QColor color;

    red_component.clearMembers();
    green_component.clearMembers();
    blue_component.clearMembers();

    for (QPointF point : vector_points)
    {

        color = image.pixelColor(static_cast<int>(point.x()),
                                 static_cast<int>(point.y()));

        red_component.sumUpdate(color.red());
        green_component.sumUpdate(color.green());
        blue_component.sumUpdate(color.blue());
    }

    int rect_size = vector_points.size();

    if (rect_size > 0)
    {
        red_component.calculateColorIntensivity(rect_size);
        green_component.calculateColorIntensivity(rect_size);
        blue_component.calculateColorIntensivity(rect_size);

        color = color.fromRgb(red_component.componentColorIntensivity(),
                              green_component.componentColorIntensivity(),
                              blue_component.componentColorIntensivity());

        return color;
    }
}
//////////////////////////////////////////////////////////////////

QVector<QPointF> Interpolator::interpolatorTransform(Transform transform,
                                                     QRect rect)
{
    QVector<QPointF> vector_points;
    QPointF curr_point;

    for (int y = 0; y < rect.height(); y++)
    {
        curr_point.setY(rect.topLeft().y() + y);

        for (int x = 0; x < rect.width(); x++)
        {
            curr_point.setX(rect.topLeft().x() + x);

            vector_points.push_front(transform(curr_point));
        }
    }

    return vector_points;
}

///////////////////////////////////////////////////////////////////
