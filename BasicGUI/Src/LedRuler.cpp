
#include "LedRuler.h"
#include "FileManager.h"
#include "Interpolator.h"
#include "Transformation.h"
#include <QDebug>
#include <QPen>
#include <iostream>

LedRuler::LedRuler(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(200, 200), m_number_of_leds(30),
      m_rotation(1), m_size(1)
{
}
/////////////////////////////////////////////////////////
void LedRuler::setPixmap(QPixmap* pixmap) { m_interpolator.setPixmap(pixmap); }
////////////////////////////////////////////////////////
void LedRuler::saveImage() { qDebug() << m_output_image->save("result.png"); }

////////////////////////////////////////////////////////
void LedRuler::paint(QPainter* painter)
{
    painter->translate(m_point);
    QPoint offset(m_size * 0.5, m_size * (-0.5));
    QPoint pixel{0, 0};

    int width = static_cast<int>(360 / m_rotation) + 1;
    if (m_output_image != nullptr)
        delete m_output_image;

    m_output_image = new QImage(m_number_of_leds, width, QImage::Format_RGB32);

    int k = 0;
    for (int rot = 0; rot < 360; rot += m_rotation)
    {
        pixel.setY(k++);

        painter->save();
        painter->rotate(rot);
        QRect rect{offset, QSize{m_size, m_size}};

        for (int i = 0; i < m_number_of_leds; i++)
        {
            pixel.setX(i);
            rect.moveTo(rect.topLeft() + QPoint{m_size, 0});

            QColor color = m_interpolator.interpolatorSetLedColor(
                m_interpolator.interpolatorTransform(Transform{m_point, rot},
                                                     rect));
            if (color.isValid())
                m_output_image->setPixelColor(pixel, color);
            else
                break;

            QPen pen{painter->pen()};
            pen.setColor(Qt::transparent);
            painter->setPen(pen);
            painter->setBrush(color);
            painter->drawRect(rect);
        }

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