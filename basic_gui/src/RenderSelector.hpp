#pragma once

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

class RenderSelector : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    RenderSelector(QQuickItem* parent = 0);
    void paint(QPainter* painter) override;

    Q_INVOKABLE void setPoint(QPoint point);
    Q_INVOKABLE void selectorUpdate(int number_of_leds, int size);

private:
    QPoint m_point; // środek odrysowywania
    int m_number_of_leds;
    int m_size;
};

