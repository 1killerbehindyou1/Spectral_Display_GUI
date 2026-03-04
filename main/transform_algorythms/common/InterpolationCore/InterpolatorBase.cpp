#include "InterpolatorBase.hpp"

namespace common
{

QImage InterpolatorBase::transformImage(int ang_resolution, int no_pixels,
                                        QPoint transform_center,
                                        const QPixmap* pix_map)
{
    /**
     * Validate input parameters before any processing.
     * This ensures that the function operates on valid data and prevents potential errors.
     */
    if (ang_resolution <= 0 || no_pixels <= 0 || pix_map == nullptr || pix_map->isNull())
    {
        return {};
    }

    /**
     * Number of angular samples needed to cover the full 360 degrees.
     * This ensures that the entire circle is sampled based on the angular resolution.
     */
    const int width = (360 + ang_resolution - 1) / ang_resolution;
    QImage output_image{no_pixels, width, QImage::Format_RGB32};

    /**
     * Iterate over LED radius positions (columns in output image).
     * This represents the distance from the transform center along the horizontal axis.
     */
    for (int led_idx = 1; led_idx < no_pixels; ++led_idx)
    {
        /**
         * Current sampling point on the horizontal ray from transform center.
         * This point represents the position along the radius at the current LED index.
         */
        const QPoint curr_rect_corner{transform_center.x() + led_idx, transform_center.y()};
        /**
         * Sample area represented as a 1x1 rectangle around current point.
         * This rectangle is used for color interpolation from the source pixmap.
         */
        const QRectF rect_f{QPointF(curr_rect_corner.x() - 0.5, curr_rect_corner.y() - 0.5), QSizeF{1.0, 1.0}};

        /**
         * Iterate over angular positions (rows in output image).
         * This represents the angle around the transform center for the current LED index.
         */
        for (int ang_idx = 0; ang_idx < width; ++ang_idx)
        {
            const double angle = static_cast<double>(ang_idx * ang_resolution);
            Transform transform{transform_center, angle};

            /**
             * Rotate the sampling rectangle and interpolate color from source pixmap.
             * This step applies the transformation to the rectangle and retrieves the corresponding color.
             */
            const auto transformed_poly_f = transform(rect_f);
            const QColor color_r = interpolateColor(transformed_poly_f, pix_map);

            if (color_r.isValid())
            {
                output_image.setPixelColor(led_idx, ang_idx, color_r);
            }
            else
            {
                /**
                 * Stop this ray when interpolation can no longer provide a valid color.
                 * This prevents further processing along this direction, optimizing performance.
                 */
                break;
            }
        }
    }

    return output_image;
}
} // namespace common