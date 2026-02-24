
#include "RenderSelector.hpp"
#include <QDebug>
#include <QPen>
#include <iostream>

RenderSelector::RenderSelector(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(400, 400), m_number_of_leds(25),
      m_size(1)
{
}

void RenderSelector::paint(QPainter* painter)
{
    int radius = m_number_of_leds * m_size;

    QPen pen = painter->pen();
    pen.setColor(Qt::transparent);
    painter->setPen(pen);
    painter->setBrush(QColor{255, 0, 0, 100});

    painter->drawEllipse(m_point, radius, radius);
}

void RenderSelector::selectorUpdate(int number_of_leds, int size)
{
    m_number_of_leds = number_of_leds;
    m_size = size;
    update();
}

void RenderSelector::setPoint(QPoint point)
{
    m_point = point;
    update();
}