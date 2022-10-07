
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "LedRuler.h"
#include <QColor>
#include <QPixmap>

class Interpolation
{
   
    public:

    int iterator =0;
    int sum =0;
    int level =0;

    static QColor setLedColor(LedRuler *led_x);
    
    /*static QColor transform(QPoint sr_obr, QPoint point, int angle)
    {

    }*/

};
#endif

