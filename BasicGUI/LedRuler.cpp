
#include "LedRuler.h"
#include "ImageViewer.h"
#include "Interpolator.h"
#include "Transformation.h"
#include <QDebug>
#include <QPen>
#include <iostream>

LedRuler::LedRuler(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(200, 200)
{
    m_interpolator.inerpolator_pixmap.load(
        "C:\\Users\\mplesniak\\Desktop\\1. "
        "Mentoring_QT_project\\Spectral_Display_GUI\\Pictures\\BITMAPA.png");
    m_number_of_leds = 10;
    m_rotation = 90;
    m_size = 10;
}

void LedRuler::paint(QPainter* painter)
{
    QVector<QVector<QColor>> m_projection;
    painter->translate(m_point);
    QPoint offset(m_size * 0.5, m_size * (-0.5));

    for (int rot = 0; rot < 360; rot += m_rotation)
    {
        QVector<QColor> single_line;
        painter->save();
        painter->rotate(rot);
        QRect rect{offset, QSize{m_size, m_size}};
        for (int i = 0; i < m_number_of_leds; i++)
        {
            rect.moveTo(rect.topLeft() + QPoint{m_size, 0});
            QColor color = m_interpolator.interpolatorSetLedColor(
                m_interpolator.interpolatorTransform(Transform{m_point, rot},
                                                     rect));

            single_line.push_front(color);

            QPen pen = painter->pen();
            pen.setColor(Qt::transparent);
            painter->setPen(pen);
            painter->setBrush(color);
            painter->drawRect(rect);
        }

        m_projection.push_front(single_line);
        painter->restore();
    }
}

void LedRuler::onParameterChanged(int number_of_leds, int rotation, int size)
{
    m_number_of_leds = number_of_leds;
    m_rotation = rotation;
    m_size = size;
    update();
}

void LedRuler::setPoint(QPoint point)
{
    m_point = point;
    update();
}