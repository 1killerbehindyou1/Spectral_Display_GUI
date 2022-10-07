
#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

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

class ImageViewer : public QQuickPaintedItem{

    Q_OBJECT
    QML_ELEMENT

public:
    ImageViewer(QQuickItem *parent = 0);

    void paint(QPainter *painter) override;
    void imageViewreUpdate();
    static QPixmap m_map;         //wczytana bitmapa jak obraz

 Q_INVOKABLE bool setPixMap(const QUrl &path);

signals: 
    void fileErrLoad(QString title, QString name);
    
    
};
#endif

