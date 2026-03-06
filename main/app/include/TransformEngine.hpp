#pragma once
#include <InterpolatorSingle.hpp>
#include <QImage>
#include <QObject>
#include <QPixmap>
#include <memory>

struct TransformParameters
{
    int ang_resolution;
    int no_pixels;
    QPoint point;
};

class TransformEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage* transformedImage READ transformedImage NOTIFY
                   transformReadyForQml)
    Q_PROPERTY(
        int transformedWidth READ transformedWidth NOTIFY transformReadyForQml)
    Q_PROPERTY(int transformedHeight READ transformedHeight NOTIFY
                   transformReadyForQml)

public:
    TransformEngine(QObject* parent = nullptr);
    void transformImage();
    QImage* transformedImage() const;
    int transformedWidth() const;
    int transformedHeight() const;

public slots:
    void setPixmap(std::shared_ptr<QPixmap> pixmap);
    void updatePoint(QPoint point);
    void updateNoOfPixels(int pixels);
    void updateAngularResolution(int ang_res);

signals:
    void transformReady(std::shared_ptr<QImage> image);
    void transformReadyForQml();

private:
    void transformImage(const TransformParameters& params);
    bool hasValidParams(const TransformParameters& params) const;

    TransformParameters m_params;
    single::InterpolatorSingle m_interpolator;
    std::shared_ptr<QPixmap> m_pixmap = nullptr;
    std::shared_ptr<QImage> m_transformed_image = nullptr;
};
