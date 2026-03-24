
#include "RenderEngine.hpp"
#include <QElapsedTimer>
#include <QPixmap>
#include <QTimer>
#include <algorithm>
#include <cmath>

RenderEngine::RenderEngine(QObject* parent)
    : QObject(parent), m_render_params{300, QSize{3, 3}, 1, 2, 600}
{
    m_repaint_timer = new QTimer(this);
    m_repaint_timer->setInterval(16);
    m_repaint_timer->setTimerType(Qt::PreciseTimer);
    m_rotation_clock = new QElapsedTimer();
    m_rotation_clock->start();

    QObject::connect(
        m_repaint_timer, &QTimer::timeout, this,
        [this]()
        {
            if (!m_rendering || m_image == nullptr)
            {
                return;
            }

            const qint64 delta_ms = m_rotation_clock->restart();
            const qreal delta_seconds = static_cast<qreal>(delta_ms) / 1000.0;
            const qreal degrees_per_second =
                static_cast<qreal>(m_render_params.rotation_speed) * 6.0;

            m_rotation_degrees = std::fmod(
                m_rotation_degrees + (degrees_per_second * delta_seconds),
                360.0);

            if (m_rotation_degrees < 0.0)
            {
                m_rotation_degrees += 360.0;
            }

            requestRepaint();
        });

    m_repaint_timer->start();
}

RenderEngine::~RenderEngine() {}

QImage* RenderEngine::image() const { return m_image; }

int RenderEngine::ledSize() const { return m_render_params.led_size.width(); }

int RenderEngine::ledDistance() const { return m_render_params.led_distance; }

int RenderEngine::ledCount() const { return m_render_params.no_pixels; }

void RenderEngine::setImage(QImage* image) { m_image = image; }

void RenderEngine::setPixmap(QPixmap* pixmap)
{
    if (pixmap == nullptr || pixmap->isNull())
    {
        return;
    }

    m_owned_image = pixmap->toImage();
    m_image = &m_owned_image;
    m_render_params.no_pixels = pixmap->width();
    emit ledCountChanged();
}

void RenderEngine::startRendering(bool flag)
{
    m_rendering = flag;
    if (m_rendering && m_rotation_clock != nullptr)
    {
        m_rotation_clock->restart();
    }
}

void RenderEngine::updateNoOfPixels(int pixels)
{
    if (pixels > 0)
    {
        m_render_params.no_pixels = pixels;
        emit ledCountChanged();
    }
}

void RenderEngine::updateLedSize(int size)
{
    m_render_params.led_size = QSize{size, size};
    emit ledSizeChanged();
}

void RenderEngine::updateLedDistance(int distance)
{
    m_render_params.led_distance = distance;
    emit ledDistanceChanged();
}

void RenderEngine::updateAngularResolution(int ang_res)
{
    m_render_params.led_arc_resolution = ang_res;
}

void RenderEngine::updateRotationSpeed(int speed)
{
    m_render_params.rotation_speed = std::clamp(speed, 1, 6000);
}

void RenderEngine::requestRepaint()
{
    if (m_image != nullptr)
    {
        const int image_height = m_image->height();
        if (image_height > 0)
        {
            m_render_params.led_arc_resolution =
                static_cast<int>(360 / image_height);
        }
    }
}

// void RenderEngine::paint(QPainter* painter)
// {
//     if (m_rendering && m_image != nullptr)
//     {
//         const int spacing = m_render_params.led_size.width() +
//         m_render_params.led_distance; if (spacing <= 0)
//         {
//             return;
//         }

//         const int led_number = m_render_params.no_pixels / spacing;

//         if (m_render_params.led_distance < 0)
//         {
//             return;
//         }

//         const int image_height = m_image->height();
//         if (image_height <= 0)
//         {
//             return;
//         }

//         const qreal normalized_rotation = m_rotation_degrees / 360.0;
//         const int rotation_degrees = static_cast<int>(m_rotation_degrees);
//         const int image_row = static_cast<int>(normalized_rotation *
//         image_height) % image_height;

//         painter->translate(m_render_center);

//             painter->save();
//             painter->rotate(rotation_degrees);

//             QRectF current_led_rect{QPointF{0, 0}, m_render_params.led_size};

//             for (int led_idx = 0; led_idx < led_number; led_idx++)
//             {
//                 current_led_rect.moveLeft(led_idx *
//                 (m_render_params.led_size.width() +
//                 m_render_params.led_distance));

//                 QColor color{};
//                 if (m_image->valid({led_idx, image_row}))
//                 {
//                     color =  m_image->pixelColor(led_idx, image_row);
//                 }
//                 else
//                 {
//                     color = "grey";
//                 }
//                 painter->setPen(Qt::transparent);
//                 painter->setBrush(color);
//                 painter->drawRect(current_led_rect);
//             }

//             painter->restore();
//     }
