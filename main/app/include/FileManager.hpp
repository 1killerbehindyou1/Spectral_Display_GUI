#pragma once

#include <QDebug>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QUrl>
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
    void fileReadyToTransform(QPixmap pixmap);

private:
    QPixmap m_pixmap;
    QPixmap m_transformed;
    QString m_path;
};
