
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

class FileManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path MEMBER m_path)
    Q_PROPERTY(QPixmap* pixmap_pointer READ getPixmapPointer)

public:
    FileManager(QObject* parent = 0);
    QPixmap* getPixmapPointer();

    QPixmap m_pixmap;
    QPixmap m_transformed;
    QString m_path;

public slots:
    bool loadPixMap(QUrl path);

signals:
    void fileErrLoad(QString title, QString name);
    void setImageOnGui();
};
#endif
