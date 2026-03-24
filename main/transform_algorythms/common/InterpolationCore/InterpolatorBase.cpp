#include "InterpolatorBase.hpp"

namespace common
{

QImage InterpolatorBase::transformImage(int ang_resolution, int no_pixels,
                                        QPoint transform_center,
                                        const QPixmap* pix_map)
{
    if (ang_resolution <= 0 || no_pixels <= 0 || pix_map == nullptr ||
        pix_map->isNull())
    {
        return {};
    }

    const int width = (360 + ang_resolution - 1) / ang_resolution;
    QImage output_image{no_pixels, width, QImage::Format_RGB32};

    for (int led_idx = 1; led_idx < no_pixels; ++led_idx)
    {
        const QPoint curr_rect_corner{transform_center.x() + led_idx,
                                      transform_center.y()};
        const QRectF rect_f{
            QPointF(curr_rect_corner.x() - 0.5, curr_rect_corner.y() - 0.5),
            QSizeF{1.0, 1.0}};

        for (int ang_idx = 0; ang_idx < width; ++ang_idx)
        {
            const double angle = static_cast<double>(ang_idx * ang_resolution);
            Transform transform{transform_center, angle};

            const auto transformed_poly_f = transform(rect_f);
            const QColor color_r =
                interpolateColor(transformed_poly_f, pix_map);

            if (color_r.isValid())
            {
                output_image.setPixelColor(led_idx, ang_idx, color_r);
            }
            else
            {
                break;
            }
        }
    }

    return output_image;
}
} // namespace common