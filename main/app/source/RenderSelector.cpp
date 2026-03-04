
#include "RenderSelector.hpp"
#include <QDebug>
#include <QPen>
#include <iostream>

RenderSelector::RenderSelector(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(200, 200), m_radius(100)
{
}

void RenderSelector::paint(QPainter* painter)
{

    QPen pen = painter->pen();
    pen.setColor(Qt::transparent);
    painter->setPen(pen);
    painter->setBrush(QColor{255, 0, 0, 100});

    painter->drawEllipse(m_point, m_radius, m_radius);
}

void RenderSelector::selectorResize(int new_size)
{
    qDebug() << "line:" << __LINE__ << ", file: RenderSelector.cpp\t"
            << "Selector resize called with new size:" << new_size;
    m_radius = new_size;
    update();
}

void RenderSelector::setPoint(QPoint point)
{
    m_point = point;
    update();
}