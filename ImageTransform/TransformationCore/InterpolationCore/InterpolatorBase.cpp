#include "InterpolatorBase.hpp"

namespace common
{

QImage InterpolatorBase::transformImage(int deg_angle, int led_size,
                                        int number_of_leds,
                                        const QPixmap* pix_map)
{

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);

    int width = static_cast<int>(360 / deg_angle);
    QImage output_image{number_of_leds, width, QImage::Format_RGB32};

    QPoint curr_rect_corner = rot_centr;

    for (int led_idx = 1; led_idx < number_of_leds; led_idx++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + led_size);
        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect_f{temp_point, QSize{led_size, led_size}};
        rect_f.moveCenter(curr_rect_corner);

        double angle = 0;
        for (int ang_idx = 0; angle < 360.0;
             ++ang_idx, angle = deg_angle * ang_idx)
        {
            Transform transform{rot_centr, angle};
            QPointF transformed_curr_rect_corner = transform(curr_rect_corner);

            auto transformed_poly_f = transform(rect_f);
            QPoint pixel{led_idx, ang_idx};

            QColor color_r = interpolateColor(transformed_poly_f, pix_map);

            if (color_r.isValid())
                output_image.setPixelColor(pixel, color_r);
            else
                break;
        }
    }
    return output_image;
}
} // namespace common