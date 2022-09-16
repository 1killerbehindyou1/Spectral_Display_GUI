
#include "LedRuler.h"
#include "Interpolation.h"
#include <iostream>
#include <QDebug>

LedRuler::LedRuler(QQuickItem *parent): QQuickPaintedItem(parent), m_number_of_leds(20), m_size(10),
           m_pix_rect(new QRect[m_number_of_leds]), m_color(new QColor[m_number_of_leds]), m_map("C:/Users/mplesniak/Desktop/1. Mentoring_QT_project/Spectral_Display_GUI/Pictures/BITMAPA.png")    
{
    int x = 0;
    int y = 0;
    for(int i =0; m_number_of_leds > i; i++)
    {
        m_pix_rect[i].setHeight(m_size);
        m_pix_rect[i].setWidth(m_size);
        m_pix_rect[i].moveTo(x, y);
        x += (m_size + m_spacing);
    }
    std::cout<< "LED Ruler constructor" << std::endl;
    
}

void LedRuler::setSize( const int &size)
{
    m_size = size;
    for(int i =0; m_number_of_leds > i; i++)
    {
        m_pix_rect[i].setHeight(size);
        m_pix_rect[i].setWidth(size);
    }
}

int LedRuler::size() const { return m_size ;}

int LedRuler::lx() const { return m_pix_rect[0].x(); }

int LedRuler::ly() const { return m_pix_rect[0].y() ;}

void LedRuler::setLx(const int &lx) { m_pix_rect[0].setX(lx); }

void LedRuler::setLy(const int &ly) { m_pix_rect[0].setY(ly); }

int LedRuler::rotation() const { return m_rotation; }

void LedRuler::setRotation(const int &rotation) { m_rotation = rotation; }

int LedRuler::spacing() const { return m_spacing; }

void LedRuler::setSpacing(const int &spacing) { m_spacing = spacing; }

int LedRuler::number_of_leds() const { return m_number_of_leds; }

void LedRuler::setNumber_of_leds(const int &number_of_leds) { m_number_of_leds = number_of_leds; }

QPixmap LedRuler::getPixMap() const{ return m_part_map; }

void LedRuler::setPixMap(QPixmap pix){ m_part_map = pix; }

void LedRuler::paint(QPainter *painter)
{
    painter->drawPixmap(0,0,m_map);
    painter->translate(m_map.width()/2, m_map.height()/2);
    
    for(int rot = 0; rot <= 360; rot += 5){
        painter->rotate(rot);
        for(int i =0; m_number_of_leds > i; i++)
        {
            painter->setBrush(m_color[i]);
            painter->drawRect(m_pix_rect[i]);
        }
    }
}

void LedRuler::rulerUpdate(int x,int y, int rotation)
{
    m_rotation = rotation;
    for(int i =0; m_number_of_leds > i; i++)
    {
        m_pix_rect[i].moveTo(x - m_size, y - m_size);
        m_part_map = m_map.copy(m_pix_rect[i]);

        m_color[i] = Interpolation::setLedColor(this);
        x += (m_spacing + m_size);
    }
    update();
}

void LedRuler::pointUpdate(int x, int y)
{
    m_point.setX(x);
    m_point.setY(y);
    update();
}
