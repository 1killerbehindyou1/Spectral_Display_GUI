#pragma once

#include <QPoint>
#include <QtQuick/QQuickPaintedItem>

class QPainter;

class RenderSelector : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    RenderSelector(QQuickItem* parent = nullptr);
    void paint(QPainter* painter) override;

    Q_INVOKABLE void setPoint(QPoint point);
    Q_INVOKABLE void selectorResize(int no_pixels);

private:
    QPoint m_point; // środek odrysowywania
    int m_radius; // promień zaznaczenia
};