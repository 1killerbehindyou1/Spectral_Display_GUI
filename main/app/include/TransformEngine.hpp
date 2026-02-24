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

class TransformEngine : public QObject
{
    Q_OBJECT

public:
    TransformEngine(QObject* parent = 0);
    void transformImage(int number_of_leds = 30, int rotation = 1, int size = 3, QPoint point = QPoint(200, 200));

public slots:
    void setPixmap(std::shared_ptr<QPixmap> pixmap) { m_pixmap = pixmap; }

signals:
    void transformReady(std::shared_ptr<QImage> image);
    void transformReadyForQml();

private:
    Interpolator m_interpolator;
    std::shared_ptr<QPixmap> m_pixmap = nullptr;
    std::shared_ptr<QImage> m_transformed_image = nullptr;
};
