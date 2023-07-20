
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

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

public slots:
    bool loadPixMap(QUrl path);
    void savePixMap(QUrl path, QImage* output_image);

signals:
    void fileErrLoad(QString title, QString name);
    void setImageOnGui();

private:
    QPixmap m_pixmap;
    QPixmap m_transformed;
    QString m_path;
};
#endif
