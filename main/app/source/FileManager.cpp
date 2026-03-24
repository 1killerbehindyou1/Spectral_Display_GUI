
#include "FileManager.hpp"
#include <QFileInfo>
#include <QUrl>

FileManager::FileManager(QObject* parent) : QObject(parent) {}

QPixmap* FileManager::getPixmapPointer() { return &m_pixmap; }

QString FileManager::lastLoadedPath() const { return m_last_loaded_path; }

QString FileManager::lastSavedPath() const { return m_last_saved_path; }

void FileManager::savePixMap(QUrl path, QImage* output_image)
{
    QString qstr = path.toLocalFile();

    if (!path.isLocalFile() || qstr.isEmpty())
    {
        emit fileErrLoad("Save file failed",
                         "Invalid output path. Please select local file path.");
        return;
    }

    if (output_image == nullptr || output_image->isNull())
    {
        emit fileErrLoad("Save file failed",
                         "Output image is empty. Render image before saving.");
        return;
    }

    QFileInfo output_info(qstr);
    if (output_info.suffix().isEmpty())
    {
        qstr += ".png";
    }

    if (!output_image->save(qstr))
    {
        emit fileErrLoad("Save file failed",
                         "Could not write image to selected path.");
        return;
    }

    m_last_saved_path = qstr;
    emit lastSavedPathChanged();
}

bool FileManager::loadPixMap(QUrl path)
{
    if (!path.isLocalFile())
    {
        emit fileErrLoad(
            "Loaded file failed",
            "File is not local. Please select a file from your local storage.");
        return false;
    }

    return loadPixMapInternal(path.toLocalFile());
}

bool FileManager::loadPixMapFromLocalPath(QString localPath)
{
    return loadPixMapInternal(std::move(localPath));
}

QString FileManager::toFileUrl(QString localPath) const
{
    return QUrl::fromLocalFile(localPath).toString();
}

bool FileManager::loadPixMapInternal(QString localPath)
{
    if (localPath.isEmpty())
    {
        emit fileErrLoad("Loaded file failed", "File path is empty.");
        return false;
    }

    QImage img{};

    if (!img.load(localPath))
    {
        emit fileErrLoad("Loaded file failed",
                         "File is corrupted or isn't graphic file");
        return false;
    }

    m_pixmap = QPixmap::fromImage(std::move(img));

    if (m_pixmap.isNull())
    {
        emit fileErrLoad("Loaded file failed",
                         "File is corrupted or isn't graphic file");
        return false;
    }
    m_path = localPath;
    m_last_loaded_path = localPath;

    emit setImageOnGui();
    emit fileReadyToTransform(m_pixmap);
    emit fileLoadedSize(m_pixmap.width(), m_pixmap.height());
    emit lastLoadedPathChanged();

    return true;
}
