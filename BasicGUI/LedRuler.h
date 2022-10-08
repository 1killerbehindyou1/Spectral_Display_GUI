
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

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

class LedRuler : public QQuickPaintedItem{

    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int step READ step WRITE setStep)
    Q_PROPERTY(int number_of_leds READ number_of_leds WRITE setNumber_of_leds)
    QML_ELEMENT

public:
    LedRuler(QQuickItem *parent = 0);

    int number_of_leds() const;
    void setNumber_of_leds(const int &number);

    int spacing() const;
    void setSpacing(const int &spacing);

    int step() const;
    void setStep(const int &number);

    int size() const;
    void setSize(const int &size);

    int rotation() const;
    void setRotation(const int &rotation);

    void paint(QPainter *painter) override;

    static QVector<QColor *>* m_projection;

 Q_INVOKABLE void rulerUpdate();
 Q_INVOKABLE void setPoint(const QPoint &point);
 Q_INVOKABLE void setAcquire(bool set);

public slots:
    void onBitMapLoadedCorrectly(QPixmap pixmap);

signals:
    void acquisitionFinished();

private:
    
    QPoint m_point;        // środek odrysowywania
    QPixmap m_pixmap;

    int m_number_of_leds;
    int m_rotation;
    int m_spacing;
    int m_size;
    int m_step;
    bool m_acquire_data_flag = true;
   
};
#endif

