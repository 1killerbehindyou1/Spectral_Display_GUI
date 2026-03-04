#pragma once
#include <QDebug>
#include <QObject>
#include <QPixmap>
#include <QUrl>
#include <QImage>
#include <memory>

#include <InterpolatorSingle.hpp>

// Convenience alias for the interpolator type
using TransformInterpolator = single::InterpolatorSingle;

struct TransformParameters
{
    int ang_resolution;
    int no_pixels;
    QPoint point;
};

class TransformEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage* transformedImage READ transformedImage NOTIFY transformReadyForQml)
    Q_PROPERTY(int transformedWidth READ transformedWidth NOTIFY transformReadyForQml)
    Q_PROPERTY(int transformedHeight READ transformedHeight NOTIFY transformReadyForQml)

public:
    TransformEngine(QObject* parent = 0);
    void transformImage();
    void transformImage(int ang_resolution, int no_pixels, QPoint point);
    QImage* transformedImage() const { return m_transformed_image.get(); }
    int transformedWidth() const { return m_transformed_width; }
    int transformedHeight() const { return m_transformed_height; }

public slots:
    void setPixmap(std::shared_ptr<QPixmap> pixmap)
    {
         m_pixmap = pixmap;
            m_has_logged_missing_pixmap = false;
         qDebug() << "line:" << __LINE__ << ", file: TransformEngine.cpp\t"
                  << "Pixmap set in TransformEngine with size:" << m_pixmap->size();
    }
    void updatePoint(QPoint point);
    void updateNoOfPixels(int pixels);
    void updateAngularResolution(int ang_res);

signals:
    void transformReady(std::shared_ptr<QImage> image);
    void transformReadyForQml();

private:
    void transformImage(const TransformParameters& params);
    bool warnNoPixmapIfNeeded();

    TransformParameters m_params;
    TransformInterpolator m_interpolator;
    std::shared_ptr<QPixmap> m_pixmap = nullptr;
    bool m_has_logged_missing_pixmap = false;
    std::shared_ptr<QImage> m_transformed_image = nullptr;
    int m_transformed_width = 0;
    int m_transformed_height = 0;
};
