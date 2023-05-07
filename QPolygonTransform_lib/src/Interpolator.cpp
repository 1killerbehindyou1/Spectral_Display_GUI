
#include "Interpolator.h"
#include <QColor>
#include <QDebug>
#include <cmath>
#include <iostream>

namespace QPolyLib
{

namespace color
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
} // namespace color

Interpolator::Interpolator(QObject* parent)
    : QObject(parent), inerpolator_pixmap(nullptr)
{
}
void Interpolator::setPixmap(QPixmap* pixmap) { inerpolator_pixmap = pixmap; }

QColor Interpolator::interpolateColor(const QPolygonF& transformed_poly)
{
    using namespace QPolyLib::color;
    if (inerpolator_pixmap != nullptr)
    {
        QPoint curr_point{};
        QColor led_color{};

        QImage image{inerpolator_pixmap->toImage()};

        int count{};
        QRectF rect_boundig_f = transformed_poly.boundingRect();
        for (int y = 0; y < rect_boundig_f.height(); y++)
        {
            curr_point.setY(rect_boundig_f.topLeft().y() + y);

            for (int x = 0; x < rect_boundig_f.width(); x++)
            {
                curr_point.setX(rect_boundig_f.topLeft().x() + x);

                if (image.valid(curr_point) &&
                    (transformed_poly.containsPoint(curr_point,
                                                    Qt::OddEvenFill)))
                {
                    count++;
                    led_color += image.pixelColor(curr_point);

                    qDebug()
                        << led_color << "+" << image.pixelColor(curr_point);
                    qDebug() << count;
                }
            }
        }
        qDebug() << "led_color / count" << led_color / count;
        return led_color / count;
    }
    else
        return QColor{};
}

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
            Transform transform{
                rot_centr,
                (led_idx == 0 ? ang_idx : (int)(ang_idx / deg_angle))};
            QPointF transformed_curr_rect_corner = transform(curr_rect_corner);

            auto transformed_poly_f = transform(QPolygonF(rect_f));
            QPoint pixel{led_idx,
                         (led_idx == 0 ? ang_idx : (int)(ang_idx / deg_angle))};

            QColor color_r = interpolateColor(transformed_poly_f);

            if (color_r.isValid())
                output_image.setPixelColor(pixel, color_r);
            else
                break;
        }
    }
    return output_image;
}
} // namespace QPolyLib