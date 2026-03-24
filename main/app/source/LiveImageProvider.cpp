#include "LiveImageProvider.hpp"

LiveImageProvider::LiveImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image)
{
}

const QImage& LiveImageProvider::image() const { return m_image_transformed; }

void LiveImageProvider::setImage(const QImage& img)
{
    m_image_transformed = img;
}

QImage LiveImageProvider::requestImage(const QString& str, QSize* size,
                                       const QSize& requestedSize)
{
    if (size)
    {
        *size = m_image_transformed.size();
    }
    if (requestedSize.isValid())
    {
        return m_image_transformed.scaled(requestedSize);
    }
    return m_image_transformed;
}