
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

Interpolator::Interpolator(QObject* parent)
    : QObject(parent), inerpolator_pixmap(nullptr)
{
}
void Interpolator::setPixmap(QPixmap* pixmap) { inerpolator_pixmap = pixmap; }

QColor Interpolator::interpolateColor(Transform transform, const QRectF& rect)
{
    if (inerpolator_pixmap != nullptr)
    {
        QPolygonF transformed_poly; // poligon with transformed points
        transformed_poly << transform(rect.topLeft())
                         << transform(rect.bottomLeft())
                         << transform(rect.bottomRight())
                         << transform(rect.topRight());
        QPoint curr_point{};
        QColor led_color{};
        QRectF bounding_rect{transformed_poly.boundingRect()};
        QImage image{inerpolator_pixmap->toImage()};

        int count{};

        for (int y = 0; y < bounding_rect.height(); y++)
        {
            curr_point.setY(bounding_rect.topLeft().y() + y);

            for (int x = 0; x < bounding_rect.width(); x++)
            {
                curr_point.setX(bounding_rect.topLeft().x() + x);

                if (image.valid(curr_point) &&
                    (transformed_poly.containsPoint(curr_point,
                                                    Qt::OddEvenFill)))
                {
                    count++;
                    led_color += image.pixelColor(curr_point);
                }
            }
        }
        // qDebug() << rect;
        // Debug() << transformed_poly;
        // qDebug() << bounding_rect;
        // qDebug() << count;
        return led_color / count;
    }
    else
        return QColor{};
}

QImage Interpolator::transformImage(int deg_angle, int led_size,
                                    int number_of_leds)
{

    QPointF rot_centr(inerpolator_pixmap->width() / 2,
                      inerpolator_pixmap->height() / 2);

    QRectF rect{QPoint{static_cast<int>(led_size * 0.5),
                       static_cast<int>(led_size * (-0.5))},
                QSize{led_size, led_size}};
    int width = static_cast<int>(360 / deg_angle);

    QImage output_image{number_of_leds, width, QImage::Format_RGB32};

    QPoint pixel{0, 0};
    int k = 0;
    for (int rot = 0; rot <= 360; rot += deg_angle)
    {
        Transform transformator{rot_centr, rot};
        pixel.setY(k++);

        for (int i = 0; i < number_of_leds; i++)
        {
            pixel.setX(i);
            rect.moveTo(rect.topLeft() + QPointF{rect.width(), 0});

            QColor color = interpolateColor(transformator, rect);
            if (color.isValid())
                output_image.setPixelColor(pixel, color);
            else
                break;
        }
    }
    return output_image;
}
