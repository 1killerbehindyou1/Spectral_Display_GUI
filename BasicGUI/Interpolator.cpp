
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

    QColor led_color{
        0,
        0,
        0,
    };

    for (QPointF point : vector_points)
    {
        increaseTotalInensivity(led_color,
                                image.pixelColor(static_cast<int>(point.x()),
                                                 static_cast<int>(point.y())));
    }

    int rect_size = vector_points.size();

    if (rect_size > 0)
    {
        return led_color = calculateaAverageIntensivity(rect_size, led_color);
    }
    else
    {
        led_color.setRgb(0, 0, 0);
        return led_color;
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
namespace
{
void increaseTotalInensivity(QColor& color, QColor color_from_image)
{

    color.setRedF(color.redF() + color_from_image.redF());
    color.setGreenF(color.greenF() + color_from_image.greenF());
    color.setBlueF(color.blueF() + color_from_image.blueF());
}

QColor calculateaAverageIntensivity(int sample_amount, QColor total_intensivity)
{
    QColor color;
    color.setRedF(total_intensivity.redF() / sample_amount);
    color.setGreenF(total_intensivity.greenF() / sample_amount);
    color.setBlueF(total_intensivity.blueF() / sample_amount);

    return color;
}
} // namespace
