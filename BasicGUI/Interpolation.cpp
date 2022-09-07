
#include "Interpolation.h"

void Interpolation::setLedColor(LedRuler *led_x)
{   
    QPixmap pixmap(led_x->getPixMap());
    QImage image = pixmap.toImage(); 
   
    QColor color;
    int it_white =0;
    int it_black =0;
    int level_drakness = 0;

    for (int x = 0; x < image.width(); ++x) {
    
    for (int y = 0; y < image.height(); ++y) {
        color = image.pixelColor(x,y);

        if(color == Qt::black) it_black ++;
        if(color == Qt::white) it_white ++;
        
    }
    }

    if(it_black > 0 || it_white > 0) 
    {
        level_drakness = 255 * it_white/(it_black + it_white);
    }
    else level_drakness = 1;
   

    color = color.fromRgb(level_drakness, level_drakness, level_drakness);
    led_x->setColor(color);

    
}




