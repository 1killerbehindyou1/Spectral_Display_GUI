
#include "RenderSelector.hpp"
#include <QDebug>
#include <QPen>
#include <iostream>

RenderSelector::RenderSelector(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(400, 400), m_radius_px(25)
{
}

void RenderSelector::paint(QPainter* painter)
{
    // painter->translate(m_point);
    QPen pen = painter->pen();
    pen.setColor(Qt::transparent);
    painter->setPen(pen);
    painter->setBrush(QColor{255, 0, 0, 100});
    painter->drawEllipse(m_point, m_radius_px, m_radius_px);
}

void RenderSelector::selectorUpdate(int radius)
{
    m_radius_px = radius;
    update();
}

void RenderSelector::setPoint(QPoint point)
{
    m_point = point;
    update();
}