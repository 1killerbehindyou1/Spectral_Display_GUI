
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Transformation.h"
#include <Constants.hpp>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>
namespace QPolyLib
{
namespace color
{

QColor operator/(const QColor& total_intensivity, int sample_amount);
QColor operator+=(QColor& color_a, const QColor& color_b);

} // namespace color

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
} // namespace QPolyLib
#endif
