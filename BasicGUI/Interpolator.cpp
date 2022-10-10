
#include "Interpolator.h"
#include <iostream>
#include <QDebug>
#include <cmath>

Interpolator::Interpolator(QObject* parent) :QObject(parent){

}


QColor Interpolator::interpolatorSetLedColor(QVector<QPoint> vector_points)
{  
        QImage image = inerpolator_pixmap.toImage(); 
        QColor color;

        red_component.sum =0;
        green_component.sum =0;
        blue_component.sum =0;
        red_component.level =0;
        green_component.level =0;
        blue_component.level=0;

        for(QPoint point : vector_points){

            color = image.pixelColor(point);
            std::cout << "point X:  " <<  point.x()  << "  point Y:  " << point.y()  << std::endl;
            
            red_component.sum += color.red();
            green_component.sum += color.green();
            blue_component.sum += color.blue();
        }

        std::cout << "KKKKKKKKKKKKKK  " << std::endl;
        int rect_size = pow(vector_points.size(),2);
        
        if(rect_size > 0){
        red_component.level = red_component.sum/rect_size;
        green_component.level = green_component.sum/rect_size;
        blue_component.level = blue_component.sum/rect_size;
        }
        
        //std::cout << "size blue_component.level:  " <<  blue_component.level  << std::endl;
        //std::cout << "blue_component.sum:  " <<  blue_component.sum  << std::endl;
        //std::cout << "rect_size:  " <<  rect_size  << std::endl;
        /*std::cout << "size blue_component.level:  " <<  blue_component.level  << std::endl;
        std::cout << "size green_component.level:  " <<  green_component.level  << std::endl;
        std::cout << "size red_component.level:  " <<  red_component.level  << std::endl;*/

        return color = color.fromRgb(red_component.level, green_component.level, blue_component.level);
    
}
/*
        Function Interpolator::interpolatorTransform 
        creates a vector points, which are contained in actually checked rectangle
*/

QVector<QPoint> Interpolator::interpolatorTransform(QPoint center_of_rot, QRect rect, int angle)
{
        QVector<QPoint> vector_points;
        QPoint rect_top_left = rect.topLeft();
       
        PointInReferenceSystem current_point;
        degreeToRad(angle);

        
        for(int yy =0; yy <= rect.height();  yy++){   
        
            current_point.point.setY(rect_top_left.y() + yy);

            for(int xx =0; xx <= rect.width();  xx++){   
                
                current_point.point.setX(rect_top_left.x() + xx);
                
                current_point.calcModule(); 
                current_point.calcAngle();
               
                current_point.angle += m_angle; 

                current_point.calcPoint();
                vector_points.push_front(current_point.point);
            }
        }
        return vector_points;
}

void Interpolator::degreeToRad(int angle){ m_angle = angle * 3.14/180; }

void PointInReferenceSystem::calcModule(){ module = sqrt(pow(point.x(),2) + pow(point.y(),2)); }

void PointInReferenceSystem::calcAngle(){ angle = acos(point.x()/module);}

void PointInReferenceSystem::calcPoint(){
    point.setX(module*cos(angle ));  
    point.setY(module*sin(angle ));
}