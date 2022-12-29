
#ifndef LED_RULER_H
#define LED_RULER_H

#include "Interpolator.h"
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

class LedRuler : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QPixmap* pixmap WRITE setPixmap)

public:
    void setPixmap(QPixmap* pixmap);
    LedRuler(QQuickItem* parent = 0);
    void paint(QPainter* painter) override;

    Q_INVOKABLE void setPoint(QPoint point);
    Q_INVOKABLE void showOutputPreview(bool show);
    Q_INVOKABLE void saveImage();
    Q_INVOKABLE void onParameterChanged(int number_of_leds, int rotation,
                                        int size);

private:
    QPixmap* m_pixmap = 0;
    QImage* m_output_image = 0;
    QPoint m_point; // środek odrysowywania
    Interpolator m_interpolator;
    int m_number_of_leds;
    int m_rotation;
    int m_size;
    bool m_out_img_prev;
};
#endif
