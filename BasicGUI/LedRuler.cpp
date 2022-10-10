
#include "LedRuler.h"
#include "Interpolator.h"
#include "ImageViewer.h"
#include <iostream>
#include <QDebug>
#include <QPen>
#include "DataManager.h"

LedRuler::LedRuler(QQuickItem *parent)
                : QQuickPaintedItem(parent){

    m_interpolator.inerpolator_pixmap.load("C:\\Users\\mplesniak\\Desktop\\1. Mentoring_QT_project\\Spectral_Display_GUI\\Pictures\\BITMAPA.png");
    m_number_of_leds = 1;
    m_rotation = 360;
    m_spacing = 0;
    m_size =2;
}

void LedRuler::paint(QPainter *painter)
{
    DataManager::m_projection = new (QVector<QVector<QColor>>); 

    painter->translate(m_point);
    QPoint offset(m_size * 0.5, m_size *(-0.5));
    

    for(int rot = 0; rot < 360; rot += m_rotation){ 
        
        QVector<QColor> single_line;       
        QRect rect{offset, QSize {m_size, m_size}};
        painter->save();
        painter->rotate(rot);
        
       for(int i =0; i < m_number_of_leds ; i++)
        {
            rect.moveTo(rect.topLeft() + QPoint{m_spacing + m_size, 0});
            QColor color = m_interpolator.interpolatorSetLedColor(m_interpolator.interpolatorTransform(m_point, rect, rot)); 
            
            single_line.push_front(color);

            QPen pen = painter->pen();
            pen.setColor(Qt::transparent);
            painter->setPen(pen);
            painter->setBrush(color);
            painter->drawRect(rect);
        }
         
        DataManager::m_projection->push_front(single_line);
        painter->restore();
    }
}

void LedRuler::onParameterChanged(int number_of_leds, int spacing, int rotation, int size)
{
    m_number_of_leds = number_of_leds;
    m_rotation = rotation;
    m_spacing = spacing;
    m_size = size;
    update();
}

void LedRuler::setPoint(QPoint point) {
    
     m_point = point; 
     update();
}