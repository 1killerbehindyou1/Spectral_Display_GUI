
#include "Interpolator.h"
#include <iostream>
#include <QDebug>
#include <cmath>

Interpolator::Interpolator(QObject *parent) : QObject(parent)
{
}

QColor Interpolator::interpolatorSetLedColor(QVector<QPointF> vector_points)
{
    QImage image = inerpolator_pixmap.toImage();
    QColor color;

    red_component.sum = 0;
    green_component.sum = 0;
    blue_component.sum = 0;
    red_component.level = 0;
    green_component.level = 0;
    blue_component.level = 0;

    for (QPointF point : vector_points)
    {

        color = image.pixelColor(static_cast<int>(point.x()), static_cast<int>(point.y()));

        //std::cout << " SetLedColor() point X:  " << point.x() << " SetLedColor() point Y:  " << point.y() << std::endl;

        red_component.sum += color.red();
        green_component.sum += color.green();
        blue_component.sum += color.blue();
    }

    
    int rect_size = vector_points.size();

    if (rect_size > 0)
    {
        red_component.level = red_component.sum / rect_size;
        green_component.level = green_component.sum / rect_size;
        blue_component.level = blue_component.sum / rect_size;
    }
   
    return color = color.fromRgb(red_component.level, green_component.level, blue_component.level);
}
/*
        Function Interpolator::interpolatorTransform
        creates a vector points, which are contained in actually checked rectangle
*/

QVector<QPointF> Interpolator::interpolatorTransform(QPoint center_of_rot, QRect rect, float deg_angle)
{
    QVector<QPointF> vector_points;
    QPointF rect_top_left = rect.topLeft();
     PointInReferenceSystem current_point;
    float ext_angle = current_point.convertAngleToRad(deg_angle);

  
    for (int yy = 0; yy < rect.height(); yy++)
    {
        current_point.point.setY(rect_top_left.y() + yy);
         
        for (int xx = 0; xx < rect.width(); xx++)
        {
             current_point.point.setX(rect_top_left.x() + xx);
            
            current_point.calcAngle();
            current_point.calcModule();
            current_point.updateAngle(ext_angle);
            current_point.updatePoint(center_of_rot);
            vector_points.push_front(current_point.point);

            current_point.angle =0;
            current_point.point.setY(rect_top_left.y() + yy);
            current_point.point.setX(rect_top_left.x() + xx); 
        }
    }
    return vector_points;
} 

float PointInReferenceSystem::convertAngleToRad(float ext_angle) {return ext_angle * 3.14159 / 180; }

void PointInReferenceSystem::calcAngle() { angle = atan2(point.y(), point.x()); }
void PointInReferenceSystem::calcModule(){  module = point.x()/cosf(angle); }

void PointInReferenceSystem::updateAngle(float ext_angle){ angle += ext_angle; }

void PointInReferenceSystem::updatePoint(QPoint center_of_rot){

    point.setX(module * cos(angle) + center_of_rot.x()); 
    point.setY(module * sin(angle) + center_of_rot.y()); 
}