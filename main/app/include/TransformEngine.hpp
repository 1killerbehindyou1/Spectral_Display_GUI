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

public:
    TransformEngine(QObject* parent = 0);
    void transformImage();
    void transformImage(int number_of_leds, int rotation, int size, QPoint point);

public slots:
    void setPixmap(std::shared_ptr<QPixmap> pixmap) { m_pixmap = pixmap; }
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
};
