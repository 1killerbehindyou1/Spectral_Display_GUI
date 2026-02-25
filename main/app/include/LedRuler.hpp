#pragma once

#include <InterpolatorQPoly.hpp>
#include <QColor>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QString>
#include <QUrl>
#include <QVector>
#include <QtQuick/QQuickPaintedItem>
#include <cmath>
#include <iostream>

// Convenience alias for the interpolator type
using Interpolator = poly::InterpolatorQPoly;

class LedRuler : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QPixmap* pixmap READ pixmap WRITE setPixmap)

public:
    LedRuler(QQuickItem* parent = 0);
    void paint(QPainter* painter) override;
    QPixmap* pixmap() const;
    void setPixmap(QPixmap* pixmap);

    Q_INVOKABLE void setPoint(QPoint point);
    Q_INVOKABLE void showOutputPreview(bool show);
    Q_INVOKABLE void onParameterChanged(int number_of_leds, int rotation,
                                        int size);

private:
    QPixmap* m_pixmap = nullptr;
    QImage* m_current_transformed_image = nullptr;
    QPoint m_point; // środek odrysowywania
    Interpolator m_interpolator;
    int m_number_of_leds;
    int m_rotation;
    int m_size;
    bool m_rendered_preview;
};
