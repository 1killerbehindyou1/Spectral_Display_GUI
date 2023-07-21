
#ifndef QPOLY_INTERPOLATION_H
#define QPOLY_INTERPOLATION_H

#include <ColorCalc.h>
#include <QColor>
#include <QDebug>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>
#include <iostream>

namespace QPolyLib
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
} // namespace QPolyLib
#endif
