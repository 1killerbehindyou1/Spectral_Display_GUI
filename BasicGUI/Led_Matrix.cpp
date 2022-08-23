
#include "Led_Matrix.h"
#include <QDebug>

LedMatrix::LedMatrix(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}


QString LedMatrix::name() const
{
    return m_name;
}

void LedMatrix::setName(const QString &name)
{
    m_name = name;
}

QColor LedMatrix::color() const
{
    return m_color;
}

void LedMatrix::setColor(const QColor &color)
{
    m_color = color;
}

void LedMatrix::paint(QPainter *painter)
{
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
}