
#include "Interpolator.h"
#include <iostream>
#include <QDebug>
#include <cmath>

QColor Interpolation::setLedColor(QVector<QPoint> vector_points, QPixmap pixmap)
{   
    QImage image = pixmap.toImage(); 
   
    QColor color;
    Interpolation red_pixels;
    Interpolation green_pixels;
    Interpolation blue_pixels;

    for(QPoint point : vector_points){

        color = image.pixelColor(point);

        red_pixels.sum += color.red();
        green_pixels.sum += color.green();
        blue_pixels.sum += color.blue();
    }

    
    int rect_size = vector_points.size();
    std::cout<< "ilosc pixeli:  " << rect_size<< std::endl;

    if(rect_size > 0){
    red_pixels.level = red_pixels.sum/rect_size;
    green_pixels.level = green_pixels.sum/rect_size;
    blue_pixels.level = blue_pixels.sum/rect_size;
    }
    
   //std::cout<< "red_pixels.level: " <<red_pixels.level <<" green_pixels.level: " << green_pixels.level << "blue_pixels.level: "<< blue_pixels.level<< std::endl;
    return color = color.fromRgb(red_pixels.level, green_pixels.level, blue_pixels.level);
}


QVector<QPoint> Interpolation::transform(QPoint sr_obr, QRect rect, int angle)
{
        QVector<QPoint> vector_points;
        QPoint p_top_left = rect.topLeft();
        
        QPoint wzgl_point;
        
        float rad = angle * 3.14/180;

        for(int yy =0; yy <= rect.height();  yy++){   
        
            wzgl_point.setY(p_top_left.y() + yy);

            for(int xx =0; xx <= rect.width();  xx++){   
                
                wzgl_point.setX(p_top_left.x() + xx);
                
                int R =  p_top_left.x() + xx;
                
                QPoint bezwzgl_point;  //punkty bezwględne
                bezwzgl_point.setX(R*cos(rad) + sr_obr.x());  
                bezwzgl_point.setY(R*sin(rad) + sr_obr.y());
                vector_points.push_front(bezwzgl_point);
            }
        }
        return vector_points;
}





