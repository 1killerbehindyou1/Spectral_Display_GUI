
#ifndef LED_RULER_H
#define LED_RULER_H

#include <QColor>
#include <QString>
#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QUrl>
#include <QDebug>
#include <cmath>
#include <iostream>
#include <QVector>
#include "Interpolator.h"

class LedRuler : public QQuickPaintedItem{

    Q_OBJECT
    QML_ELEMENT

public:
    LedRuler(QQuickItem *parent = 0);
    void paint(QPainter *painter) override;

 Q_INVOKABLE void setPoint(QPoint point);
 Q_INVOKABLE void onParameterChanged(int number_of_leds, int rotation, int spacing,int size);
  
private:
       
    QPoint m_point;        // środek odrysowywania
    Interpolator m_interpolator;
    int m_number_of_leds;
    int m_rotation;
    int m_spacing;
    int m_size;
    bool m_acquire_data_flag = true;
};
#endif

