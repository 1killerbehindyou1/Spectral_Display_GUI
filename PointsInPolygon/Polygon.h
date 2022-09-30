#ifndef POLYGON_P
#define POLYGON_P

#include <QString>
#include <QObject>
#include <QPoint>
#include <QtQuick/QQuickPaintedItem>
#include <QPainter>
#include <QPixmap>
#include <QUrl>
#include <QDebug>
#include <QVector> 
#include <iostream>
#include <cmath>


class T_Polygon : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint a READ A_point WRITE setA_Point)
    Q_PROPERTY(QPoint b READ B_point WRITE setB_Point)
    Q_PROPERTY(QPoint c READ C_point WRITE setC_Point)
    Q_PROPERTY(QPoint d READ D_point WRITE setD_Point)
    QML_ELEMENT

public:
    T_Polygon(QQuickItem *parent = 0);

    QPoint A_point() const;
    void setA_Point( QPoint A);

    QPoint B_point() const;
    void setB_Point( QPoint B);

    QPoint C_point() const;
    void setC_Point(QPoint C);

    QPoint D_point() const;
    void setD_Point(QPoint D);

    void paint(QPainter *painter) override;
    QPolygon translate(int agle, QPoint top_left, int side);

   Q_INVOKABLE bool setPixMap(const QUrl &path);
   Q_INVOKABLE void polygonUpdate(int angle, QPoint m_top_left, int m_side);

signals: 
    void fileErrLoad(QString title, QString name);

private:
    QPoint m_A;   
    QPoint m_B;
    QPoint m_C;
    QPoint m_D;
    QPixmap m_map;
    QPolygon m_poly;
    int m_angle;
    int m_side;
    QPoint m_top_left;
};
#endif