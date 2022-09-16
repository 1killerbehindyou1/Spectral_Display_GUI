
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <QColor>
#include <QString>
#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QPainter>
#include <QPixmap>
#include <QUrl>
#include <QDebug>
#include <iostream>

class LedRuler : public QQuickPaintedItem{

    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int number_of_leds READ number_of_leds WRITE setNumber_of_leds)
    QML_ELEMENT

public:
    LedRuler(QQuickItem *parent = 0);

    int number_of_leds() const;
    void setNumber_of_leds(const int &number);

    int spacing() const;
    void setSpacing(const int &number);

    int size() const;
    void setSize(const int &size);

    int rotation() const;
    void setRotation(const int &rotation);

    QPixmap getPixMap() const;
    void setPixMap(QPixmap pix);

     void paint(QPainter *painter) override;

 Q_INVOKABLE void rulerUpdate();

private:
    
    QRect *m_pix_rect;   //wskaźnik do tablicy kwadratów
    QPixmap m_map;         //wczytana bitmapa jak obraz
    QPixmap m_part_map;  //bitmapa pobrana z obrazka
    QColor *m_color;     //tablica zmiennych kolor
    
    int m_number_of_leds;
    int m_rotation;
    int m_spacing;
    int m_size;
};
#endif

