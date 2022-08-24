
#include "Led_Matrix.h"
#include <QDebug>

LedMatrix::LedMatrix(QQuickItem *parent): QQuickPaintedItem(parent), m_draw_area(0,0, 600, 520), m_point(0, 0), m_pix_rect(0,0, 50,50),
            m_pix_map("C:/Users/mplesniak/Desktop/1. Mentoring_QT_project/Spectral_Display_GUI/Pictures/szachy.png")    
{
    m_rotation =0;  
}


QColor LedMatrix::color() const
{
    return m_color;
}

void LedMatrix::setColor(const QColor &color)
{
    m_color = color;
}

void LedMatrix::setSize( const int &size)
{
    m_size.setHeight(size);
    m_size.setWidth(size);
}

int LedMatrix::size() const
{
    return m_size.height();
}

int LedMatrix::lx() const
{
    return m_point.x();
}

int LedMatrix::ly() const
{
    return m_point.y();
}

void LedMatrix::setLx(const int &lx) 
{
     m_point.setX(lx);
}

void LedMatrix::setLy(const int &ly) 
{
     m_point.setY(ly);
}

int LedMatrix::rotation() const 
{
    return m_rotation;
}

void LedMatrix::setRotation(const int &rotation)
{
    m_rotation = rotation;
}

void LedMatrix::paint(QPainter *painter)
{
    QPen pen(m_color, 2);
    painter->setPen(pen);
    
    painter->setBrush(m_pix_map);
    painter->drawRect(m_draw_area);

    painter->setBrush(m_color);
    painter->rotate(m_rotation);
    painter->drawRect(m_point.x(),m_point.y(),m_size.height(), m_size.width());
}


void LedMatrix::matrixUpdate(int x,int y, int rotation)
{
    m_rotation = rotation;
    m_point.setX(x); 
    m_point.setY(y); 

    m_pix_rect.setSize(m_size);
    m_pix_rect.setTopLeft(m_point);

    update();
    //emit matrixUpdated();
}
