
#include "FileManager.hpp"
#include <QDebug>
#include <QFileInfo>
#include <iostream>

FileManager::FileManager(QObject* parent) : QObject(parent) {}

QPixmap* FileManager::getPixmapPointer() { return &m_pixmap; }

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

    QString qstr = path.toLocalFile(); // zamiana ścieżki na sciezke do pliku lokanego
    QImage img{};

    if (!img.load(qstr))
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
    m_path = qstr;

    emit setImageOnGui();
    emit fileReadyToTransform(m_pixmap);

    return true;
}
