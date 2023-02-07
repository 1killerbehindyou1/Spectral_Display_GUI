
#include "FileManager.h"
#include <QDebug>
#include <iostream>

FileManager::FileManager(QObject* parent) : QObject(parent) {}

QPixmap* FileManager::getPixmapPointer() { return &m_pixmap; }

bool FileManager::savePixMap(QUrl path)
{
    QString qstr = path.toLocalFile();
} // must waiting for merge
  // branch
  // 10-please-consider-checkable-actions-which-could-cover-both-hide-and-show-menu-entries
bool FileManager::loadPixMap(QUrl path)
{
    if (!path.isLocalFile())
    {
        emit fileErrLoad(
            "Loaded file failed",
            "Ouch! This is remote file. We don't have handling for that "
            "right now");
        return false;
    }

    QString qstr =
        path.toLocalFile(); // zamiana ścieżki na sciezke do pliku lokanego
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
        emit fileErrLoad("Loaded file failed", "Loaded file is null");
        return false;
    }
    m_path = qstr;
    emit setImageOnGui();

    return true;
}
