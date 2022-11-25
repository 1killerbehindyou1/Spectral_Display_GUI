
#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <QColor>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QString>
#include <QUrl>
#include <QtQuick/QQuickPaintedItem>
#include <cmath>
#include <iostream>

class ImageViewer : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    ImageViewer(QQuickItem* parent = 0);

    void paint(QPainter* painter) override;
    Q_INVOKABLE bool setPixMap(const QUrl& path);

signals:
    void fileErrLoad(QString title, QString name);

private:
    QPixmap m_pixmap;
};
#endif
