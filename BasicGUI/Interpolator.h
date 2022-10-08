
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "LedRuler.h"
#include <QColor>
#include <QPoint>
#include <QVector>
#include <QPixmap>

class Interpolation
{
   
public:

    int iterator =0;
    int sum =0;
    int level =0;

    static QColor setLedColor(QVector<QPoint> vector_points, QPixmap pixmap);
    
    static QVector<QPoint> transform(QPoint sr_obr, QRect rect, int angle);
    
};
#endif

