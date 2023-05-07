
#include "LedRuler.h"
#include "FileManager.h"
#include "Interpolator.h"
#include "Transformation.h"
#include <QDebug>
#include <QPen>
#include <iostream>

LedRuler::LedRuler(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_point(200, 200), m_number_of_leds(30),
      m_rotation(1), m_size(1), m_rendered_preview(false)
{
}
/////////////////////////////////////////////////////////
void LedRuler::setPixmap(QPixmap* pixmap) { m_interpolator.setPixmap(pixmap); }
////////////////////////////////////////////////////////
QImage* LedRuler::getRenderedImage() { return m_output_image; }
////////////////////////////////////////////////////////
void LedRuler::paint(QPainter* painter)
{
    if (m_current_transformed_image != nullptr)
    {
        // painter->save();
        // QSize::QSize(int width, int height)
        painter->drawImage(QPoint{0, 0}, *m_current_transformed_image);

        int lp_width = m_current_transformed_image->width();
        int lp_hight = m_current_transformed_image->height();

        int diff_angle = int(360 / lp_hight);
        qDebug() << "width: " << lp_width; // << lp_hight;
        qDebug() << "diff_angle: " << diff_angle;
        qDebug() << *m_current_transformed_image;

        // painter->save();
        painter->translate(250, 250);

        for (int curr_rot = 0; curr_rot < 360; curr_rot += diff_angle)
        {
            // painter->save();
            //  painter->rotate(curr_rot);
            qDebug() << "curr_rot: " << curr_rot;
            QRect current_led_rect{QPoint{0, 0}, QSize{m_size, m_size}};

            painter->save();
            for (int led_idx = 0; led_idx < lp_width; led_idx++)
            {

                painter->rotate(curr_rot);
                // qDebug() << "led_idx: " << led_idx;
                current_led_rect.moveLeft(led_idx * m_size);
                QPen pen{painter->pen()};
                pen.setColor(Qt::transparent);

                if (m_current_transformed_image->valid(
                        {curr_rot / diff_angle, led_idx}))
                {
                    QColor color{m_current_transformed_image->pixelColor(
                        curr_rot / diff_angle, led_idx)};

                    if (color.isValid())
                    {
                        // qDebug() << curr_rot << led_idx;
                        //  qDebug() << color;
                        painter->setBrush(color);
                        painter->drawRect(current_led_rect);
                    }
                }
            }
            painter->restore();
        }
    }
    delete m_current_transformed_image;
}

void LedRuler::onParameterChanged(int number_of_leds, int rotation, int size)
{
    m_number_of_leds = number_of_leds;
    m_rotation = rotation;
    m_size = size;
    m_current_transformed_image = new QImage{
        m_interpolator.transformImage(rotation, size, number_of_leds)};
    update();
}

void LedRuler::setPoint(QPoint point)
{
    m_point = point;
    qDebug() << m_point;
    this->onParameterChanged(m_number_of_leds, m_rotation, m_size);
}

void LedRuler::showOutputPreview(bool show)
{
    m_rendered_preview = show;
    update();
}
