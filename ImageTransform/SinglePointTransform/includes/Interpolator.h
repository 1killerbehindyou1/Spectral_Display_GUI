
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <Transformation.h>
#include <cmath>
#include <iostream>

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

#endif
