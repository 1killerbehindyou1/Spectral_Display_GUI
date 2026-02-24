#include "TransformEngine.hpp"

TransformEngine::TransformEngine(QObject* parent) : QObject(parent) {}

void TransformEngine::transformImage(int number_of_leds, int rotation, int size,
                                    QPoint point)
{
    if (m_pixmap == nullptr)
    {
        qDebug() << "No pixmap set for transformation.";
        return;
    }

    qDebug() << "Transforming image with parameters:"
             << "Number of LEDs:" << number_of_leds
             << "Rotation:" << rotation
             << "Size:" << size
             << "Point:" << point;

    // Perform the transformation using the interpolator
    QImage transformedImage = m_interpolator.transformImage(
        rotation, size, number_of_leds, point, m_pixmap.get());

    // Update the pixmap with the transformed image
    m_pixmap = std::make_shared<QPixmap>(QPixmap::fromImage(transformedImage));

    // Emit signal to notify that transformation is ready
    emit transformReady(m_pixmap);
}