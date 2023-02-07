
#include "RenderSelector.h"
#include <QDebug>
#include <QPen>
#include <iostream>

RenderSelector::RenderSelector(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(200, 200), m_number_of_leds(30),
      m_size(1)
{
}

////////////////////////////////////////////////////////
void RenderSelector::paint(QPainter* painter)
{
    int radius = m_number_of_leds * m_size;
    qDebug() << radius << m_point;
    painter->translate(m_point);
    painter->drawEllipse(m_point, radius, radius);
}

void RenderSelector::selectorUpdate(int number_of_leds, int size)
{
    m_number_of_leds = number_of_leds;
    m_size = size;
    qDebug() << m_size << m_number_of_leds;
    update();
}

void RenderSelector::setPoint(QPoint point)
{
    m_point = point;
    update();
}