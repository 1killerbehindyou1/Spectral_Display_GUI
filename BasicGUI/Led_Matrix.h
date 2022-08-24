
#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <QString>
#include <QObject>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>
#include <QPixmap>


class LedMatrix : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int size READ size WRITE setSize)
    Q_PROPERTY(int lx READ lx WRITE setLx)
    Q_PROPERTY(int ly READ ly WRITE setLy)
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)

    QML_ELEMENT

public:
    LedMatrix(QQuickItem *parent = 0);

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



 Q_INVOKABLE void matrixUpdate(int l_x, int l_y, int rotation );

signals:
    //void updatedMatrix();

private:
    
    QColor m_color;
    int m_size;
    int m_rotation;
    int m_lx;
    int m_ly;
};
#endif

