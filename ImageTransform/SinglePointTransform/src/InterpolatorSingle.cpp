#include "InterpolatorSingle.hpp"

namespace single
{
using namespace common;

QColor InterpolatorSingle::interpolateColor(const QPolygonF& transformed_poly)
{
    if (interpolator_pixmap != nullptr)
    {
        QImage image{interpolator_pixmap->toImage()};
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
} // namespace single