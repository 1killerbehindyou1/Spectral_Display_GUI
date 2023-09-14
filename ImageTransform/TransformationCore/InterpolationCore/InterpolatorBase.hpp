#pragma once
#include <QPixmap>
#include <Transformation.hpp>

namespace common
{

class InterpolatorBase
{

public:
    virtual QColor interpolateColor(const QPolygonF& transformed_poly) = 0;

    void setPixmap(QPixmap* pixmap) { interpolator_pixmap = pixmap; }
    QImage transformImage(int deg_angle, int led_size, int number_of_leds);

protected:
    QPixmap* interpolator_pixmap{nullptr};
};
}; // namespace common
