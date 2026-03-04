#pragma once

#include <InterpolatorBase.hpp>
#include <QColor>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QString>
#include <QUrl>
#include <QVector>
#include <QtQuick/QQuickPaintedItem>
#include <cmath>
#include <iostream>

// Convenience alias for the interpolator type
using LedInterpolatorBase = common::InterpolatorBase;

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
