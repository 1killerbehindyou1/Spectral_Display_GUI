
#include "Led_Matrix.h"
#include <QDebug>

LedMatrix::LedMatrix(QQuickItem *parent): QQuickPaintedItem(parent)
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
    m_size = size;
}

int LedMatrix::size() const
{
    return m_size;
}

int LedMatrix::lx() const
{
    return m_lx;
}

int LedMatrix::ly() const
{
    return m_ly;
}

void LedMatrix::setLx(const int &lx) 
{
     m_lx = lx;
}

void LedMatrix::setLy(const int &ly) 
{
     m_ly = ly;
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
    QPixmap pix("C:/Users/mplesniak/Desktop/1. Mentoring_QT_project/Spectral_Display_GUI/Pictures/szachy.png");

    painter->setBrush(Qt::blue);
    painter->rotate(m_rotation);
    painter->drawRect(m_lx, m_ly, m_size, m_size);
}



void LedMatrix::matrixUpdate(int x,int y, int rotation)
{
    m_rotation = rotation;
    m_lx = x;
    m_ly = y;
    update();
    //emit matrixUpdated();
}
