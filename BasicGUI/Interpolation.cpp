
#include "Interpolation.h"
#include <iostream>
#include <QDebug>

QColor Interpolation::setLedColor(LedRuler *led_x)
{   
    QPixmap pixmap(led_x->getPixMap());
    QImage image = pixmap.toImage(); 
   
    QColor color;
    Interpolation red_pixels;
    Interpolation green_pixels;
    Interpolation blue_pixels;

   for (int x = 0; x < image.width(); ++x) {
    
    for (int y = 0; y < image.height(); ++y) {
        color = image.pixelColor(x,y);

                red_pixels.sum += color.red();
                green_pixels.sum += color.green();
                blue_pixels.sum += color.blue();
        }
    }
    
    int image_size = image.height() * image.height();

    if(image_size > 0){
    red_pixels.level = red_pixels.sum/image_size;
    green_pixels.level = green_pixels.sum/image_size;
    blue_pixels.level = blue_pixels.sum/image_size;
    }
    
    return color = color.fromRgb(red_pixels.level, green_pixels.level, blue_pixels.level);
}




