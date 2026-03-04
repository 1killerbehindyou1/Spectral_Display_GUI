
#include "LedRuler.hpp"
#include "FileManager.hpp"
#include <QPainter>
#include <QPen>
#include <Transformation.hpp>
#include <thread>
#include <chrono>

LedRuler::LedRuler(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_render_params{30, QSize{3, 3}, 1, 2}, m_render_center{0, 0}, m_render_radius(50)
{
}

QImage* LedRuler::image() const
{
    return m_image;
}

void LedRuler::setImage(QImage* image)
{
    m_image = image;
    update();
}

void LedRuler::setPixmap(QPixmap* pixmap)
{
    if (pixmap == nullptr || pixmap->isNull())
    {
        return;
    }

    m_owned_image = pixmap->toImage();
    m_image = &m_owned_image;
    update();
}

void LedRuler::startRendering(bool flag)
{
    m_rendering = flag;
    update();
}

void LedRuler::requestRepaint()
{
    if (m_image != nullptr)
    {
        m_image->size() = QSize{m_image->width(), m_image->height()};
        m_render_params.led_arc_resolution = static_cast<int>(360 /  m_image->size().height());

        const qreal center_x = width() > 0 ? width() / 2.0 : 250.0;
        const qreal center_y = height() > 0 ? height() / 2.0 : 250.0;
        m_render_center = QPoint(center_x, center_y);
        update();
    }
}

void LedRuler::paint(QPainter* painter)
{
    if (m_rendering && m_image != nullptr)
    {
        painter->translate(m_render_center);

        for (int curr_rot = 0; curr_rot < m_image->size().height(); curr_rot++)
        {
            painter->save();
            painter->rotate(curr_rot * m_render_params.led_arc_resolution);

            QRect current_led_rect{QPoint{0, 0}, m_render_params.led_size};

            for (int led_idx = 0; led_idx < m_image->size().width(); led_idx++)
            {
                current_led_rect.moveLeft(m_render_params.led_distance + led_idx * m_render_params.led_size.width());

                QColor color{};
                if (m_image->valid({led_idx, curr_rot}))
                {
                    color =  m_image->pixelColor(led_idx, curr_rot);
                }
                else
                {
                    color = "grey";
                }

                painter->setPen(Qt::transparent);
                painter->setBrush(color);
                painter->drawRect(current_led_rect);
            }
            painter->restore();
        }
    }
}