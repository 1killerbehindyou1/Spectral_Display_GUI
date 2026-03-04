#include "TransformEngine.hpp"
#include <QDebug>

TransformEngine::TransformEngine(QObject* parent) : QObject(parent), m_params{} {}

QImage* TransformEngine::transformedImage() const
{
    return m_transformed_image.get();
}

int TransformEngine::transformedWidth() const
{
    return m_transformed_width;
}

int TransformEngine::transformedHeight() const
{
    return m_transformed_height;
}

void TransformEngine::setPixmap(std::shared_ptr<QPixmap> pixmap)
{
    m_pixmap = pixmap;
    m_has_logged_missing_pixmap = false;
}
bool TransformEngine::warnNoPixmapIfNeeded()
{
    if (m_pixmap != nullptr)
    {
        m_has_logged_missing_pixmap = false;
        return false;
    }

    if (!m_has_logged_missing_pixmap)
    {
        m_has_logged_missing_pixmap = true;
    }

    return true;
}

void TransformEngine::transformImage()
{
    if (warnNoPixmapIfNeeded())
    {
        return;
    }
    transformImage(m_params);
}

void TransformEngine::transformImage(const TransformParameters& params)
{
    if (warnNoPixmapIfNeeded())
    {
        return;
    }

    if (params.no_pixels <= 0 || params.ang_resolution <= 0 || params.point.isNull())
    { return;}

    if (params.point.x() < 0 || params.point.y() < 0 ||
        params.point.x() >= m_pixmap->width() ||
        params.point.y() >= m_pixmap->height())
    { return;}

    // Perform the transformation using the interpolator
    auto transformed_image = m_interpolator.transformImage(
        params.ang_resolution, params.no_pixels, params.point, m_pixmap.get());

    m_transformed_image = std::make_shared<QImage>(std::move(transformed_image));
    m_transformed_width = m_transformed_image->width();
    m_transformed_height = m_transformed_image->height();

    // Emit signal to notify that transformation is ready
    emit transformReady(m_transformed_image);
    emit transformReadyForQml();
}

void TransformEngine::transformImage(int no_pixels, int ang_resolution, QPoint point)
{
    transformImage(TransformParameters{ang_resolution, no_pixels, point});
}

void TransformEngine::updatePoint(QPoint point)
{
    m_params.point = point;
    transformImage(m_params);
}

void TransformEngine::updateNoOfPixels(int pixels)
{
    m_params.no_pixels = pixels;
    transformImage(m_params);
}

void TransformEngine::updateAngularResolution(int ang_res)
{
    m_params.ang_resolution = ang_res;
    transformImage(m_params);
}