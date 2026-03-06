#pragma once

#include <QImage>
#include <QObject>
#include <QSize>

class QPixmap;
class QTimer;
class QElapsedTimer;

struct RenderParameters
{
    int no_pixels;
    QSize led_size;
    int led_arc_resolution;
    int led_distance;
    int rotation_speed;
};

class RenderEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage* image READ image WRITE setImage)
    Q_PROPERTY(int ledSize READ ledSize NOTIFY ledSizeChanged)
    Q_PROPERTY(int ledDistance READ ledDistance NOTIFY ledDistanceChanged)
    Q_PROPERTY(int ledCount READ ledCount NOTIFY ledCountChanged)

public:
    RenderEngine(QObject* parent = nullptr);
    ~RenderEngine() override;

    QImage* image() const;
    void setImage(QImage* image);
    int ledSize() const;
    int ledDistance() const;
    int ledCount() const;

    Q_INVOKABLE void setPixmap(QPixmap* pixmap);
    Q_INVOKABLE void startRendering(bool flag);
    Q_INVOKABLE void requestRepaint();
    Q_INVOKABLE void updateNoOfPixels(int pixels);
    Q_INVOKABLE void updateLedSize(int size);
    Q_INVOKABLE void updateLedDistance(int distance);
    Q_INVOKABLE void updateAngularResolution(int ang_res);
    Q_INVOKABLE void updateRotationSpeed(int speed);

signals:
    void ledSizeChanged();
    void ledDistanceChanged();
    void ledCountChanged();

private:
    bool m_rendering{true};
    QImage* m_image = nullptr; // Pointer to the image to be rendered
    QImage m_owned_image; // Internal storage when source is provided as QPixmap
    RenderParameters m_render_params; // Parameters for rendering
    QTimer* m_repaint_timer{nullptr};
    QElapsedTimer* m_rotation_clock{nullptr};
    qreal m_rotation_degrees{0.0};
};
