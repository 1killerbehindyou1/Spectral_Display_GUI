
#include "Interpolator.h"
#include <QDebug>
#include <cmath>
#include <iostream>
namespace
{
QColor operator+=(QColor& color_a, const QColor& color_b)
{
    color_a.setRedF(color_a.redF() + color_b.redF());
    color_a.setGreenF(color_a.greenF() + color_b.greenF());
    color_a.setBlueF(color_a.blueF() + color_b.blueF());

    return color_a;
}

QColor operator/(const QColor& total_intensivity, int sample_amount)
{
    QColor color;
    if (sample_amount > 0)
    {
        color.setRedF(total_intensivity.redF() / sample_amount);
        color.setGreenF(total_intensivity.greenF() / sample_amount);
        color.setBlueF(total_intensivity.blueF() / sample_amount);
    }
    return color;
}
} // namespace
//////////////////////////////////////////////////////////////////
Interpolator::Interpolator(QObject* parent)
    : QObject(parent), inerpolator_pixmap(nullptr)
{
}
void Interpolator::setPixmap(QPixmap* pixmap) { inerpolator_pixmap = pixmap; }
//////////////////////////////////////////////////////////////////
QColor Interpolator::interpolateColor(const QPolygonF& transformed_poly)
{

    if (inerpolator_pixmap != nullptr)
    {
        QImage image{inerpolator_pixmap->toImage()};
        int count{};
        QColor led_color{};
        for (const QPointF& curr_point_f : transformed_poly)
        {
            QPoint curr_point{curr_point_f.toPoint()};
            if (image.valid(curr_point))
            {
                count++;
                led_color += image.pixelColor(curr_point);
            }
        }

        return led_color / count;
    }
    else
        return QColor{};
}

////////////////////////////////////////////////////////

QImage Interpolator::transformImage(int deg_angle, int led_size,
                                    int number_of_leds)
{

    QPoint rot_centr(inerpolator_pixmap->width() / 2,
                     inerpolator_pixmap->height() / 2);

    int width = static_cast<int>(360 / deg_angle);
    QImage output_image{number_of_leds, width, QImage::Format_RGB32};

    QPoint curr_rect_corner = rot_centr;

    for (int led_idx = 1; led_idx < number_of_leds; led_idx++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + led_size);
        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect_f{temp_point, QSize{led_size, led_size}};
        rect_f.moveCenter(curr_rect_corner);

        for (int ang_idx = 0; ang_idx <= 360 - deg_angle; ang_idx += deg_angle)
        {
            Transform transform{rot_centr, ang_idx};
            QPointF transformed_curr_rect_corner = transform(curr_rect_corner);

            auto transformed_poly_f = transform(QPolygonF(rect_f));
            QPoint pixel{led_idx, ang_idx};

            QColor color_r = interpolateColor(transformed_poly_f);

            if (color_r.isValid())
                output_image.setPixelColor(pixel, color_r);
            else
                break;
        }
    }
    return output_image;
}
