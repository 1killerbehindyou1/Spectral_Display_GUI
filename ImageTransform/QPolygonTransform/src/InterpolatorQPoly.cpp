#include "InterpolatorQPoly.hpp"

namespace poly
{

using namespace common;

QColor InterpolatorQPoly::interpolateColor(const QPolygonF& transformed_poly,
                                           const QPixmap* interpolator_pixmap)
{
    if (interpolator_pixmap != nullptr)
    {
        QPoint curr_point{};
        QColor led_color{};

        QImage image{interpolator_pixmap->toImage()};

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
                }
            }
        }
        return led_color / count;
    }
    else
        return QColor{};
}
} // namespace poly