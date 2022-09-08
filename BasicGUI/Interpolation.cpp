
#include "Interpolation.h"

void Interpolation::setLedColor(LedRuler *led_x)
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

            if(color.red() > 0)
            {
                red_pixels.iterator++;
                red_pixels.sum += color.red();
            }
            if(color.green() > 0)
            {
                green_pixels.iterator++;
                green_pixels.sum += color.green();
            }
            if(color.blue() > 0)
            {
                blue_pixels.iterator++;
                blue_pixels.sum += color.blue();
            }

        }
    }
    
    if(red_pixels.iterator > 0) 
    {
        red_pixels.level = red_pixels.sum/red_pixels.iterator;
    }
    else red_pixels.level = 0;

    if(green_pixels.iterator > 0) 
    {
        green_pixels.level = green_pixels.sum/green_pixels.iterator;
    }
    else green_pixels.level = 0;

    if(blue_pixels.iterator > 0) 
    {
        blue_pixels.level = blue_pixels.sum/blue_pixels.iterator;
    }
    else blue_pixels.level = 0;


    color = color.fromRgb(red_pixels.level, green_pixels.level, blue_pixels.level);
    led_x->setColor(color);
    
}




