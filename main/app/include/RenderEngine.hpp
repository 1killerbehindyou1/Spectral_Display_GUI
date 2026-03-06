#pragma once

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QPointF>

class QPainter;
class QThread;
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
    Q_PROPERTY(int ledSize READ ledSize NOTIFY renderParamsChanged)
    Q_PROPERTY(int ledDistance READ ledDistance NOTIFY renderParamsChanged)
    Q_PROPERTY(int ledCount READ ledCount NOTIFY renderParamsChanged)

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
    void renderParamsChanged();

private:
    bool m_rendering{true};
    QImage* m_image = nullptr; // Pointer to the image to be rendered
    QImage m_owned_image; // Internal storage when source is provided as QPixmap
    QPointF m_render_center{0, 0}; // Center point for rendering
    RenderParameters m_render_params; // Parameters for rendering
    QThread* m_repaint_thread{nullptr};
    QTimer* m_repaint_timer{nullptr};
    QElapsedTimer* m_rotation_clock{nullptr};
    qreal m_rotation_degrees{0.0};
};
