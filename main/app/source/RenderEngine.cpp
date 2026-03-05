
#include "RenderEngine.hpp"
#include "FileManager.hpp"
#include <QPainter>
#include <QPen>
#include <Transformation.hpp>
#include <thread>
#include <chrono>

RenderEngine::RenderEngine(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_render_params{30, QSize{3, 3}, 1, 2}, m_render_center{0, 0}, m_render_radius(50)
{
}

QImage* RenderEngine::image() const
{
    return m_image;
}

void RenderEngine::setImage(QImage* image)
{
    m_image = image;
    update();
}

void RenderEngine::setPixmap(QPixmap* pixmap)
{
    if (pixmap == nullptr || pixmap->isNull())
    {
        return;
    }

    m_owned_image = pixmap->toImage();
    m_image = &m_owned_image;
    update();
}

void RenderEngine::startRendering(bool flag)
{
    m_rendering = flag;
    update();
}

void RenderEngine::updateNoOfPixels(int pixels)
{
    if (pixels > 0)
    {
        m_render_params.no_pixels = pixels;
    }
    update();
}

void RenderEngine::updateLedSize(int size)
{
    m_render_params.led_size = QSize{size, size};
    update();
}

void RenderEngine::updateLedDistance(int distance)
{
    m_render_params.led_distance = distance;
    update();
}

void RenderEngine::updateAngularResolution(int ang_res)
{
    m_render_params.led_arc_resolution = ang_res;
    update();
}

void RenderEngine::requestRepaint()
{
    if (m_image != nullptr)
    {
        const int image_height = m_image->height();
        if (image_height > 0)
        {
            m_render_params.led_arc_resolution = static_cast<int>(360 / image_height);
        }

        const qreal center_x = width() > 0 ? width() / 2.0 : 250.0;
        const qreal center_y = height() > 0 ? height() / 2.0 : 250.0;
        m_render_radius = std::min(center_x, center_y); // Set radius to fit within the item
        m_render_center = QPointF(center_x, center_y);
        update();
    }
}

void RenderEngine::paint(QPainter* painter)
{
    if (m_rendering && m_image != nullptr)
    {
        const int led_size = std::max(1, m_render_params.led_size.width());
        const int led_distance = std::max(0, m_render_params.led_distance);
        const int spacing = led_size + led_distance;
        if (spacing <= 0)
        {
            return;
        }

        const int led_amount = std::max(0, m_render_params.no_pixels / spacing);

        painter->translate(m_render_center);

        for (int curr_rot = 0; curr_rot < m_image->size().height(); curr_rot++)
        {
            painter->save();
            painter->rotate(curr_rot * m_render_params.led_arc_resolution);

            QRectF current_led_rect{QPointF{0, 0}, m_render_params.led_size};

            for (int led_idx = 0; led_idx < led_amount; led_idx++)
            {
                current_led_rect.moveLeft(led_idx * spacing);

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