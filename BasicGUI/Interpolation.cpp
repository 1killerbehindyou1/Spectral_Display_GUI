
#include "Interpolation.h"

void Interpolation::setLedColor(LedMatrix *led_x)
{   
    QPixmap pixmap(led_x->getPixMap());
    QImage image = pixmap.toImage(); 
   
    QColor color;
    for (int y = 0; y < image.height(); ++y) {
    
    for (int x = 0; x < image.width(); ++x) {
        color = image.pixelColor(x,y);
        if(color == Qt::black) image.setPixelColor(x,y,"orange");
        if(color == Qt::white) image.setPixelColor(x,y,"purple");
       
    }
    }

    led_x->setPixMap(pixmap.fromImage(image));
}




