
#include "Interpolation.h"

void Interpolation::setLedColor(LedMatrix *led_x)
{   
    QPixmap pixmap(led_x->getPixMap());
    QImage image = pixmap.toImage(); 
   
    for (int y = 0; y < image.height(); ++y) {
    QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(y));
    for (int x = 0; x < image.width(); ++x) {
        QRgb &rgb = line[x];
        rgb = qRgba(qRed(rgb), qGreen(0), qBlue(rgb), qAlpha(rgb));
    }
    }
    
}



