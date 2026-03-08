#pragma once

#include <QImage>
#include <QObject>
#include <QSize>

class QPixmap;
class QTimer;
class QElapsedTimer;

/**
 * @brief Runtime rendering parameters used by the preview engine.
 */
struct RenderParameters
{
    /** @brief Number of rendered LED samples. */
    int no_pixels;

    /** @brief Size of a single LED rectangle in pixels. */
    QSize led_size;

    /** @brief Angular resolution used to map image rows to rotation angle. */
    int led_arc_resolution;

    /** @brief Gap between rendered LEDs in pixels. */
    int led_distance;

    /** @brief Rotation speed in internal units. */
    int rotation_speed;
};

/**
 * @brief QObject backend responsible for render preview state and updates.
 */
class RenderEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage* image READ image WRITE setImage)
    Q_PROPERTY(int ledSize READ ledSize NOTIFY ledSizeChanged)
    Q_PROPERTY(int ledDistance READ ledDistance NOTIFY ledDistanceChanged)
    Q_PROPERTY(int ledCount READ ledCount NOTIFY ledCountChanged)

public:
    /**
     * @brief Constructs render engine and initializes internal timers.
     * @param parent Optional QObject parent.
     */
    RenderEngine(QObject* parent = nullptr);

    /** @brief Destroys the render engine instance. */
    ~RenderEngine() override;

    /** @brief Returns currently rendered image pointer. */
    QImage* image() const;

    /** @brief Sets image used as source for rendering.
     * @param image Pointer to source image.
     */
    void setImage(QImage* image);

    /** @brief Returns current LED size in pixels. */
    int ledSize() const;

    /** @brief Returns current distance between LEDs in pixels. */
    int ledDistance() const;

    /** @brief Returns current LED count. */
    int ledCount() const;

    /** @brief Sets source image from pixmap and updates LED count.
     * @param pixmap Source pixmap pointer.
     */
    Q_INVOKABLE void setPixmap(QPixmap* pixmap);

    /** @brief Enables or disables render updates.
     * @param flag Rendering active flag.
     */
    Q_INVOKABLE void startRendering(bool flag);

    /** @brief Requests render refresh and internal recalculation. */
    Q_INVOKABLE void requestRepaint();

    /** @brief Updates number of pixels used by renderer.
     * @param pixels New LED count.
     */
    Q_INVOKABLE void updateNoOfPixels(int pixels);

    /** @brief Updates LED size.
     * @param size New LED size in pixels.
     */
    Q_INVOKABLE void updateLedSize(int size);

    /** @brief Updates distance between LEDs.
     * @param distance New distance in pixels.
     */
    Q_INVOKABLE void updateLedDistance(int distance);

    /** @brief Updates angular resolution used in rendering.
     * @param ang_res Angular resolution value.
     */
    Q_INVOKABLE void updateAngularResolution(int ang_res);

    /** @brief Updates rotation speed.
     * @param speed New rotation speed value.
     */
    Q_INVOKABLE void updateRotationSpeed(int speed);

signals:
    /** @brief Emitted when LED size changes. */
    void ledSizeChanged();
    /** @brief Emitted when LED spacing changes. */
    void ledDistanceChanged();
    /** @brief Emitted when LED count changes. */
    void ledCountChanged();

private:
    /** @brief Indicates whether render updates are active. */
    bool m_rendering{true};
    /** @brief Pointer to externally provided source image. */
    QImage* m_image = nullptr;
    /** @brief Internal image storage used when source is provided as pixmap. */
    QImage m_owned_image;
    /** @brief Runtime parameters controlling LED rendering. */
    RenderParameters m_render_params;
    /** @brief Timer driving periodic repaint requests. */
    QTimer* m_repaint_timer{nullptr};
    /** @brief Clock used to compute current rotation angle over time. */
    QElapsedTimer* m_rotation_clock{nullptr};
    /** @brief Current rotation angle in degrees. */
    qreal m_rotation_degrees{0.0};
};
