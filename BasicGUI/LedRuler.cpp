
#include "LedRuler.h"
#include "Interpolation.h"
#include <QDebug>

LedRuler::LedRuler(QQuickItem *parent): QQuickPaintedItem(parent),  
                                        m_pix_rect(0,0, 50,50)            
{
    m_rotation =0;  
}


QColor LedRuler::color() const
{
    return m_color;
}

void LedRuler::setColor(const QColor &color)
{
    m_color = color;
}

void LedRuler::setSize( const int &size)
{
    m_pix_rect.setHeight(size);
    m_pix_rect.setWidth(size);
}

int LedRuler::size() const
{
    return m_pix_rect.height();
}

int LedRuler::lx() const
{
    return m_pix_rect.x();
}

int LedRuler::ly() const
{
    return m_pix_rect.y();
}

void LedRuler::setLx(const int &lx) 
{
     m_pix_rect.setX(lx);
}

void LedRuler::setLy(const int &ly) 
{
     m_pix_rect.setY(ly);
}

int LedRuler::rotation() const 
{
    return m_rotation;
}

void LedRuler::setRotation(const int &rotation)
{
    m_rotation = rotation;
}

QPixmap LedRuler::getPixMap() const
{
    return m_part_map;
}

void LedRuler::setPixMap(QUrl path)
{
    
    QString qstr = path.toEncoded();
    m_map.load("szachy.png");
    update();
}

void LedRuler::paint(QPainter *painter)
{

    painter->drawPixmap(50, 50, m_map);
  
    painter->rotate(m_rotation);
    painter->setBrush(m_color);
    painter->drawRect(m_pix_rect);
}


void LedRuler::rulerUpdate(int x,int y, int rotation)
{
    m_rotation = rotation;
    m_pix_rect.moveTo(x - m_pix_rect.height()/2, y - m_pix_rect.height()/2);
    m_part_map = m_map.copy(m_pix_rect);

    Interpolation::setLedColor(this);

    update();
    
}
