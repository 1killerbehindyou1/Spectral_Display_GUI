
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <QString>
#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>

class Led_Matrix : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString pixel_size READ getPixelSize WRITE setPixelSize)
    Q_PROPERTY(QString number_of_pixels READ getNumberOfPixels WRITE setNumberOfPixels)
   // Q_PROPERTY(QColor pixel_color READ getColor WRITE setColor)
   
public:

    Led_Matrix(QObject *parent = 0);

    QString getPixelSize() const;
    void setPixelSize(const QString &pixel_size);

    QString getNumberOfPixels() const;
    void setNumberOfPixels(const QString &number_of_pixels);

    //QString getColor() const;
    //void setColor(const QString &pixel_color);

    //void paint(QPainter *painter);

 
private:
    QString m_pixel_size;
    QString m_number_of_pixels;
    QColor m_pixel_color;
};

#endif

