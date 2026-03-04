#include "InterpolatorBase.hpp"

namespace common
{

QImage InterpolatorBase::transformImage(int ang_resolution, int no_pixels,
                                        QPoint transform_center,
                                        const QPixmap* pix_map)
{
    int width = static_cast<int>(360 / ang_resolution);
    QImage output_image{no_pixels, width, QImage::Format_RGB32};

    QPoint curr_rect_corner = transform_center;

    for (int led_idx = 1; led_idx < no_pixels; led_idx++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + 1);
        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect_f{temp_point, QSize{1, 1}};
        rect_f.moveCenter(curr_rect_corner);

        double angle = 0;
        for (int ang_idx = 0; angle < 360.0;
             ++ang_idx, angle = ang_resolution * ang_idx)
        {
            Transform transform{transform_center, angle};
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