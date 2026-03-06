
#include "RenderSelector.hpp"
#include <QColor>
#include <QPainter>
#include <QPen>

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

void RenderSelector::selectorResize(int no_pixels)
{
    m_radius = no_pixels;
    update();
}

void RenderSelector::setPoint(QPoint point)
{
    m_point = point;
    update();
}