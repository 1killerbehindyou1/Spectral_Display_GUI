#pragma once
#include <InterpolatorSingle.hpp>
#include <QImage>
#include <QObject>
#include <QPixmap>
#include <memory>

/**
 * @brief Input parameters for image transformation.
 */
struct TransformParameters
{
    /** @brief Angular resolution in degrees. */
    int ang_resolution;

    /** @brief Number of output pixels. */
    int no_pixels;

    /** @brief Transformation center point in source image coordinates. */
    QPoint point;
};

/**
 * @brief Backend component performing image transformation for QML layer.
 */
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
    /**
     * @brief Constructs transform engine.
     * @param parent Optional QObject parent.
     */
    TransformEngine(QObject* parent = nullptr);

    /** @brief Executes transformation using currently stored parameters. */
    void transformImage();

    /** @brief Returns pointer to transformed image. */
    QImage* transformedImage() const;

    /** @brief Returns transformed image width or zero if unavailable. */
    int transformedWidth() const;

    /** @brief Returns transformed image height or zero if unavailable. */
    int transformedHeight() const;

public slots:

    /** @brief Sets source pixmap used for transformation.
     * @param pixmap Shared pointer to source pixmap.
     */
    void setPixmap(std::shared_ptr<QPixmap> pixmap);

    /** @brief Updates transformation center point and triggers transform.
     * @param point New center point.
     */
    void updatePoint(QPoint point);

    /** @brief Updates output pixel count and triggers transform.
     * @param pixels New output pixel count.
     */
    void updateNoOfPixels(int pixels);

    /** @brief Updates angular resolution and triggers transform.
     * @param ang_res New angular resolution.
     */
    void updateAngularResolution(int ang_res);

signals:
    /**
     * @brief Emitted when transformation result is ready.
     * @param image Shared pointer to transformed image.
     */
    void transformReady(std::shared_ptr<QImage> image);

    /** @brief Emitted when transformed image data is ready for QML bindings. */
    void transformReadyForQml();

private:
    void transformImage(const TransformParameters& params);
    bool hasValidParams(const TransformParameters& params) const;

    TransformParameters m_params;
    single::InterpolatorSingle m_interpolator;
    std::shared_ptr<QPixmap> m_pixmap = nullptr;
    std::shared_ptr<QImage> m_transformed_image = nullptr;
};
