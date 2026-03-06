#pragma once

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QUrl>

class FileManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path MEMBER m_path)
    Q_PROPERTY(QPixmap* pixmap_pointer READ getPixmapPointer)
    Q_PROPERTY(
        QString lastLoadedPath READ lastLoadedPath NOTIFY lastLoadedPathChanged)
    Q_PROPERTY(
        QString lastSavedPath READ lastSavedPath NOTIFY lastSavedPathChanged)

public:
    FileManager(QObject* parent = 0);
    QPixmap* getPixmapPointer();
    QString lastLoadedPath() const;
    QString lastSavedPath() const;

public slots:
    bool loadPixMap(QUrl path);
    bool loadPixMapFromLocalPath(QString localPath);
    void savePixMap(QUrl path, QImage* output_image);
    QString toFileUrl(QString localPath) const;

signals:
    void fileErrLoad(QString title, QString name);
    void setImageOnGui();
    void fileReadyToTransform(QPixmap pixmap);
    void fileLoadedSize(int width, int height);
    void lastLoadedPathChanged();
    void lastSavedPathChanged();

private:
    bool loadPixMapInternal(QString localPath);

    QPixmap m_pixmap;
    QString m_path;
    QString m_last_loaded_path;
    QString m_last_saved_path;
};
