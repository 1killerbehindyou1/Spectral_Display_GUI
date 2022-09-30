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
#include <iostream>


class T_Polygon : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint A READ A_point WRITE setA_Point)
    Q_PROPERTY(QPoint B READ B_point WRITE setB_Point)
    Q_PROPERTY(QPoint C READ C_point WRITE setC_Point)
    Q_PROPERTY(QPoint D READ D_point WRITE setD_Point)
    QML_ELEMENT

public:
    T_Polygon(QQuickItem *parent = 0);

    QPoint A_point() const;
    void setA_Point(const QPoint &A);

    QPoint B_point() const;
    void setB_Point(const QPoint &B);

    QPoint C_point() const;
    void setC_Point(const QPoint &C);

    QPoint D_point() const;
    void setD_Point(const QPoint &D);

    void paint(QPainter *painter) override;

   Q_INVOKABLE bool setPixMap(const QUrl &path);
   Q_INVOKABLE void polygonUpdate();

signals: 
    void fileErrLoad(QString title, QString name);

private:
    QPoint m_A;   
    QPoint m_B;
    QPoint m_C;
    QPoint m_D;
    QPixmap m_map;
};
#endif