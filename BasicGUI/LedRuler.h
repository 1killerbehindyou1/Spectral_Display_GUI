
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <QString>
#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>
#include <QPixmap>
#include <iostream>
#include <QDebug>


class LedRuler : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int lx READ lx WRITE setLx)
    Q_PROPERTY(int ly READ ly WRITE setLy)
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)

    QML_ELEMENT

public:
    LedRuler(QQuickItem *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

    int size() const;
    void setSize(const int &size);

    void paint(QPainter *painter) override;

    int lx() const;
    int ly() const;
    void setLx(const int &lx);
    void setLy(const int &ly);

    int rotation() const;
    void setRotation(const int &rotation);

    QPixmap getPixMap() const;
    

 Q_INVOKABLE void rulerUpdate(int l_x, int l_y, int rotation );
 Q_INVOKABLE bool setPixMap(QUrl path);

signals:
    void colorUpdate();

private:
    
    QRect m_pix_rect;   //kwadrat reprezentujacu jeden pixel
    QPixmap m_map;         //wczytana bitmapa jak obraz
    QPixmap m_part_map;  //bitmapa pobrana z obrazka

    QColor m_color;     

    int m_rotation;
    
};
#endif

