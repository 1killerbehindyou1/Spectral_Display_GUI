#pragma once

#include <QImage>
#include <QQuickImageProvider>

/**
 * @brief In-memory image provider used by QML image://live source.
 */
class LiveImageProvider : public QQuickImageProvider
{
public:
    /** @brief Constructs image provider in image mode. */
    LiveImageProvider();

    /** @brief Returns currently stored transformed image. */
    const QImage& image() const;
    /**
     * @brief Replaces current image with a new frame.
     * @param img New image frame.
     */
    void setImage(const QImage& img);

    /**
     * @brief Returns requested image frame for QML engine.
     * @param Unused source identifier.
     * @param size Optional output image size.
     * @param requestedSize Requested target size.
     * @return Stored image or scaled variant.
     */
    QImage requestImage(const QString&, QSize* size,
                        const QSize& requestedSize) override;

private:
    QImage m_image_transformed;
};
