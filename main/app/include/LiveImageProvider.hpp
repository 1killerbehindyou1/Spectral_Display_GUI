#pragma once

#include <QDebug>
#include <QQuickImageProvider>
#include <QImage>

class LiveImageProvider : public QQuickImageProvider
{
public:
    LiveImageProvider();

    const QImage& image() const;
    void setImage(const QImage& img);

    QImage requestImage(const QString&, QSize* size, const QSize& requestedSize) override;

private:
    QImage m_image_transformed;
};
