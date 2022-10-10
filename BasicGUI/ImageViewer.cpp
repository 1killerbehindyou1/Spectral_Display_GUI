
#include "ImageViewer.h"
#include <iostream>
#include <QDebug>

ImageViewer::ImageViewer(QQuickItem *parent) :QQuickPaintedItem(parent){}

bool ImageViewer::setPixMap(const QUrl &path){
    
  if (!path.isLocalFile()) {
    
    emit fileErrLoad("Loaded file failed","Ouch! This is remote file. We don't have handling for that "
                "right now");
    return false;
  }

  QString qstr = path.toLocalFile(); //zamiana ścieżki na sciezke do pliku lokanego
  QImage img{};

  if (!img.load(qstr)) {
    emit fileErrLoad("Loaded file failed","File is corrupted or isn't graphic file");
    return false;
  }

    m_pixmap  = QPixmap::fromImage(std::move(img)); 
  
   if(m_pixmap.isNull()) {

    emit fileErrLoad("Loaded file failed","Loaded file is null");
    return false;
  }
  update();

  return true;
}

void ImageViewer::paint(QPainter *painter){

      painter->drawPixmap(0,0,m_pixmap);
}

 