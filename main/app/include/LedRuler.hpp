#pragma once

#include <QObject>
#include <QImage>
#include <QPoint>
#include <QPointF>
#include <QtQuick/QQuickPaintedItem>

class QPainter;

struct RenderParameters
{
    int no_pixels;
    int arc_resolution;
    QPoint point;
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

    Q_INVOKABLE void startRendering(bool flag);
    Q_INVOKABLE void requestRepaint();

private:
    bool m_rendering{true}; // Flag to control rendering
    int m_diff_angle{0}; // Angle difference between LEDs
    QImage* m_image = nullptr; // Pointer to the image to be rendered
    QPointF m_render_center{0, 0}; // Center point for rendering
    RenderParameters m_render_params; // Parameters for rendering
};
