#pragma once
#include <QPixmap>
#include <Transformation.hpp>

namespace common
{

class InterpolatorBase
{

public:
    virtual ~InterpolatorBase();

    virtual QColor interpolateColor(const QPolygonF& transformed_poly,
                                    const QPixmap* pix_map) = 0;

    QImage transformImage(int deg_angle, int led_size, int number_of_leds,
                          const QPixmap* pix_map);
};
}; // namespace common
