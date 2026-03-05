
#include "RenderEngine.hpp"
#include "FileManager.hpp"
#include <QPainter>
#include <QPen>
#include <Transformation.hpp>
#include <thread>
#include <chrono>

RenderEngine::RenderEngine(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_render_params{300, QSize{3, 3}, 1, 2}{
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
    m_render_params.no_pixels = pixmap->width();
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
        //m_render_params.no_pixels = pixels;
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
    const qreal center_x = width() > 0 ? width() / 2.0 : 250.0;
    const qreal center_y = height() > 0 ? height() / 2.0 : 250.0;
    m_render_center = QPointF(width() / 2.0, height() / 2.0);

    if (m_image != nullptr)
    {
        const int image_height = m_image->height();
        if (image_height > 0)
        {
            m_render_params.led_arc_resolution = static_cast<int>(360 / image_height);
        }
    }

    update();
}

void RenderEngine::paint(QPainter* painter)
{
    if (m_rendering && m_image != nullptr)
    {
        //obliczam ilosc ledów
        auto led_number = m_render_params.no_pixels/ (m_render_params.led_size.width() + m_render_params.led_distance);

        if (m_render_params.led_distance < 0)
        {
            return;
        }

        painter->translate(m_render_center);

        // qDebug() << "no_pixels=" << m_render_params.no_pixels;
        // qDebug() << "paint: center=" << m_render_center;
        // qDebug() << "led_number: " << led_number;
        // qDebug() << "led_size: " << m_render_params.led_size;
        // qDebug() << "led_distance: " << m_render_params.led_distance;
        // qDebug() << "led_arc_resolution: " << m_render_params.led_arc_resolution;
        // qDebug() << "image_height: " << m_image->size().height();

        for (int curr_rot = 0; curr_rot < m_image->size().height(); curr_rot++)
        {
            painter->save();
            painter->rotate(curr_rot * m_render_params.led_arc_resolution);

            QRectF current_led_rect{QPointF{0, 0}, m_render_params.led_size};

            for (int led_idx = 0; led_idx < led_number; led_idx++)
            {
                current_led_rect.moveLeft(led_idx * (m_render_params.led_size.width() + m_render_params.led_distance));

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