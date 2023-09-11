#include "InterpolatorBase.hpp"

namespace common
{

QImage InterpolatorBase::transformImage(int deg_angle, int led_size,
                                        int number_of_leds)
{

    QPoint rot_centr(interpolator_pixmap->width() / 2,
                     interpolator_pixmap->height() / 2);

    int width = static_cast<int>(360 / deg_angle);
    QImage output_image{number_of_leds, width, QImage::Format_RGB32};

    QPoint curr_rect_corner = rot_centr;

    for (int led_idx = 1; led_idx < number_of_leds; led_idx++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + led_size);
        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect_f{temp_point, QSize{led_size, led_size}};
        rect_f.moveCenter(curr_rect_corner);

        float angle = 0;
        for (int ang_idx = 0; angle < 360.0;
             ++ang_idx, angle = deg_angle * ang_idx)
        {
            common::Transform<float, QPointF, QRectF, QPolygonF> transform{
                rot_centr, angle};
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
} // namespace common