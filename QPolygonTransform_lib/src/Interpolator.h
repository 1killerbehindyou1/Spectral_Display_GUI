
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Transformation.h"
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>

/**
 * @brief Instance of ColorColmponent Class represent single color component
 * in RGB image format.
 */

class Interpolator : public QObject
{
    Q_OBJECT

public:
    Interpolator(QObject* parent = 0);
    void setPixmap(QPixmap* pixmap);

    QColor interpolateColor(Transform transform, const QRect& rect);
    QImage transformImage(int deg_angle, int led_size, int number_of_leds);

private:
    QPixmap* inerpolator_pixmap;
};

#endif