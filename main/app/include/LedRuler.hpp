#pragma once

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QPointF>
#include <QtQuick/QQuickPaintedItem>

class QPainter;

struct RenderParameters
{
    int no_pixels;
    QSize led_size;
    int led_arc_resolution;
    int led_distance;
};

class LedRuler : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QImage* image READ image WRITE setImage)

public:
    LedRuler(QQuickItem* parent = 0);
    void paint(QPainter* painter) override;

    QImage* image() const;
    void setImage(QImage* image);
    Q_INVOKABLE void setPixmap(QPixmap* pixmap);

    Q_INVOKABLE void startRendering(bool flag);
    Q_INVOKABLE void requestRepaint();

private:
    bool m_rendering{true};
    qreal m_render_radius{0}; // Radius of the circle on which the LEDs are placed
    QImage* m_image = nullptr; // Pointer to the image to be rendered
    QImage m_owned_image; // Internal storage when source is provided as QPixmap
    QPointF m_render_center{0, 0}; // Center point for rendering
    RenderParameters m_render_params; // Parameters for rendering
};
