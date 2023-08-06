#pragma once

#include <QColor>
#include <Transformation.h>

namespace SniglePointlib
{
using namespace common;

class Interpolator : public QObject
{
    Q_OBJECT

public:
    Interpolator(QObject* parent = 0);
    void setPixmap(QPixmap* pixmap);

    QColor interpolateColor(const QPolygonF& transformed_poly);
    QImage transformImage(int deg_angle, int led_size, int number_of_leds);

private:
    QPixmap* inerpolator_pixmap;
};
} // namespace SniglePointlib

