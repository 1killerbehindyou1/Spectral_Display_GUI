#include "Polygon.h"

T_Polygon::T_Polygon(QQuickItem *parent): QQuickPaintedItem(parent){

}

QPoint T_Polygon::A_point() const{return m_A;}
void T_Polygon::setA_Point(const QPoint &A){ m_A = A; }

QPoint T_Polygon::B_point() const {return m_B;}
void T_Polygon::setB_Point(const QPoint &B){ m_B = B;}

QPoint T_Polygon::C_point() const {return m_C;}
void T_Polygon::setC_Point(const QPoint &C){ m_C = C;}

QPoint T_Polygon::D_point() const {return m_D;}
void T_Polygon::setD_Point(const QPoint &D){ m_D = D;}

bool T_Polygon::setPixMap(const QUrl &path){

    
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

  m_map = QPixmap::fromImage(std::move(img));

  if (m_map.isNull()) {
    emit fileErrLoad("Loaded file failed","Loaded file is null");
    return false;
  }
  polygonUpdate();
  return true;
}

void T_Polygon::paint(QPainter *painter)
{
     painter->drawPixmap(0,0,m_map);
     //painter->setBrush(color);
    //painter->drawRect(rect);
}

void T_Polygon::polygonUpdate(){

    update();
}