#pragma once
#include <QDebug>
#include <QObject>
#include <QPixmap>
#include <QUrl>
#include <QImage>
#include <memory>

#include <InterpolatorQPoly.hpp>

// Convenience alias for the interpolator type
using Interpolator = poly::InterpolatorQPoly;

struct TransformParameters
{
    int number_of_leds;
    int rotation;
    int size;
    QPoint point;
};

class TransformEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int transformedWidth READ transformedWidth NOTIFY transformReadyForQml)
    Q_PROPERTY(int transformedHeight READ transformedHeight NOTIFY transformReadyForQml)

public:
    TransformEngine(QObject* parent = 0);
    void transformImage();
    void transformImage(int number_of_leds, int rotation, int size, QPoint point);
    int transformedWidth() const { return m_transformed_width; }
    int transformedHeight() const { return m_transformed_height; }

public slots:
    void setPixmap(std::shared_ptr<QPixmap> pixmap)
    {
         m_pixmap = pixmap;
         qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
                  << "Pixmap set in TransformEngine with size:" << m_pixmap->size();
    }
    void updatePoint(QPoint point);
    void updateTransformParameters(int number_of_leds, int rotation, int size, QPoint point);
    void updateTransformParameters(int number_of_leds, int rotation, int size);

signals:
    void transformReady(std::shared_ptr<QImage> image);
    void transformReadyForQml();

private:
    void transformImage(const TransformParameters& params);

    TransformParameters m_params;
    Interpolator m_interpolator;
    std::shared_ptr<QPixmap> m_pixmap = nullptr;
    std::shared_ptr<QImage> m_transformed_image = nullptr;
    int m_transformed_width = 0;
    int m_transformed_height = 0;
};
