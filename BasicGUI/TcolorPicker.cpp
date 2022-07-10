/*#include "TcolorPicker.h"
#include <QPainter>

TcolorPicker::TcolorPicker(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

QColor TcolorPicker::color() const
{
    return m_color;
}

void TcolorPicker::setColor(const QColor &color)
{
    m_color = color;
}

void TcolorPicker::paint(QPainter *painter)
{
    QPen pen(m_color, 2);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 140 * 25, 290 * 16);
}

//![0]
void TcolorPicker::ChangeColor()
{
    setColor(QColor(Qt::blue));
    update();

    //emit chartCleared();
}
//![0]
*/