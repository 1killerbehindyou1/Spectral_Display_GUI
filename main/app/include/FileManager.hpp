#pragma once

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QUrl>

/**
 * @brief Handles image file loading/saving and exposes file state to QML.
 */
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
    /**
     * @brief Constructs file manager.
     * @param parent Optional QObject parent.
     */
    FileManager(QObject* parent = 0);
    /** @brief Returns pointer to currently loaded pixmap. */
    QPixmap* getPixmapPointer();
    /** @brief Returns last successfully loaded local file path. */
    QString lastLoadedPath() const;
    /** @brief Returns last successfully saved local file path. */
    QString lastSavedPath() const;

public slots:
    /**
     * @brief Loads image from file URL.
     * @param path File URL to image.
     * @return true on success, false otherwise.
     */
    bool loadPixMap(QUrl path);
    /**
     * @brief Loads image from local file system path.
     * @param localPath Local path to image.
     * @return true on success, false otherwise.
     */
    bool loadPixMapFromLocalPath(QString localPath);
    /**
     * @brief Saves output image to file URL.
     * @param path Destination file URL.
     * @param output_image Pointer to image to save.
     */
    void savePixMap(QUrl path, QImage* output_image);
    /**
     * @brief Converts local path to file URL string.
     * @param localPath Local file path.
     * @return File URL string.
     */
    QString toFileUrl(QString localPath) const;

signals:
    /**
     * @brief Emitted on load/save error.
     * @param title Error title.
     * @param name Error message body.
     */
    void fileErrLoad(QString title, QString name);
    /** @brief Emitted when image should be shown in UI. */
    void setImageOnGui();
    /**
     * @brief Emitted when source pixmap is ready for transformation.
     * @param pixmap Loaded source pixmap.
     */
    void fileReadyToTransform(QPixmap pixmap);
    /**
     * @brief Emitted when loaded image size is known.
     * @param width Image width in pixels.
     * @param height Image height in pixels.
     */
    void fileLoadedSize(int width, int height);
    /** @brief Emitted when last loaded path changes. */
    void lastLoadedPathChanged();
    /** @brief Emitted when last saved path changes. */
    void lastSavedPathChanged();

private:
    /**
     * @brief Loads image data from local file path into internal pixmap state.
     * @param localPath Local path to image file.
     * @return true on success, false otherwise.
     */
    bool loadPixMapInternal(QString localPath);

    /** @brief Internal pixmap storage used by QML and transform pipeline. */
    QPixmap m_pixmap;
    /** @brief Generic path property exposed to QML. */
    QString m_path;
    /** @brief Last successfully loaded local file path. */
    QString m_last_loaded_path;
    /** @brief Last successfully saved local file path. */
    QString m_last_saved_path;
};
