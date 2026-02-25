#include "TransformEngine.hpp"

TransformEngine::TransformEngine(QObject* parent) : QObject(parent), m_params{} {}

void TransformEngine::transformImage()
{
    if (m_pixmap == nullptr)
    {
        qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
                 << "No pixmap set for transformation.";
        return;
    }
    transformImage(m_params);
}

void TransformEngine::transformImage(const TransformParameters& params)
{
    if (m_pixmap == nullptr)
    {
        qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
                 << "No pixmap set for transformation.";
        return;
    }

    if (params.number_of_leds <= 0 || params.rotation <= 0 || params.size <= 0)
    {
        qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
                 << "Invalid transformation parameters:"
                 << "Number of LEDs:" << params.number_of_leds
                 << "Rotation:" << params.rotation
                 << "Size:" << params.size;
        return;
    }

    if (params.point.x() < 0 || params.point.y() < 0 ||
        params.point.x() >= m_pixmap->width() ||
        params.point.y() >= m_pixmap->height())
    {
        qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
                 << "Invalid point for transformation:" << params.point
                 << "with pixmap size:" << m_pixmap->size()
                 << m_pixmap->width() << "x" << m_pixmap->height() << "y";
        return;
    }

    qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
             << "Transforming image with parameters:"
             << "Number of LEDs:" << params.number_of_leds
             << "Rotation:" << params.rotation
             << "Size:" << params.size
             << "Point:" << params.point;

    // Perform the transformation using the interpolator
    auto transformed_image = m_interpolator.transformImage(
        params.rotation, params.size, params.number_of_leds, params.point, m_pixmap.get());

    m_transformed_image = std::make_shared<QImage>(std::move(transformed_image));

    // Emit signal to notify that transformation is ready
    emit transformReady(m_transformed_image);
    emit transformReadyForQml();
}

void TransformEngine::transformImage(int number_of_leds, int rotation, int size, QPoint point)
{
    transformImage(TransformParameters{number_of_leds, rotation, size, point});
}

void TransformEngine::updatePoint(QPoint point)
{
    m_params.point = point;
    transformImage(m_params);
}

void TransformEngine::updateTransformParameters(int number_of_leds, int rotation, int size, QPoint point)
{
    m_params = TransformParameters{number_of_leds, rotation, size, point};
    transformImage(m_params);
}

void TransformEngine::updateTransformParameters(int number_of_leds, int rotation, int size)
{
    m_params.number_of_leds = number_of_leds;
    m_params.rotation = rotation;
    m_params.size = size;
    transformImage(m_params);
}