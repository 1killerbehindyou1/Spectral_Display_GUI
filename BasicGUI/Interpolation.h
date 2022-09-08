
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

    static void setLedColor(LedRuler *led_x);
    

};
#endif

