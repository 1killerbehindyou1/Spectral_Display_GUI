
#include "LedRuler.h"
#include "Interpolation.h"

LedRuler::LedRuler(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_pix_rect(0,0, 50,50) {
    m_rotation =0;  
}

QColor LedRuler::color() const{ return m_color;}

void LedRuler::setColor(const QColor &color){ m_color = color; }

void LedRuler::setSize( const int &size){
    m_pix_rect.setHeight(size);
    m_pix_rect.setWidth(size);
}

int LedRuler::size() const { return m_pix_rect.height(); }

int LedRuler::lx() const { return m_pix_rect.x(); }

int LedRuler::ly() const { return m_pix_rect.y(); }

void LedRuler::setLx(const int &lx) { m_pix_rect.setX(lx); }

void LedRuler::setLy(const int &ly) { m_pix_rect.setY(ly); }

int LedRuler::rotation() const { return m_rotation; }

void LedRuler::setRotation(const int &rotation) { m_rotation = rotation; }

QPixmap LedRuler::getPixMap() const { return m_part_map; }

bool LedRuler::setPixMap(QUrl path){
  
  if (!path.isLocalFile()){

    qDebug() << "Ouch! This is remote file. We don't have handling for that "
                "right now";
    return false;
  }

  QString qstr = path.toLocalFile();
  QImage img{};

  if (!img.load(qstr)) {
    qDebug() << "Loaded file failed";
    return false;
  }

  m_map = QPixmap::fromImage(std::move(img));

  if (m_map.isNull()){
    qDebug() << "Loaded file is null";
    return false;
  }

 qDebug() << "File" << qstr << "loaded successfully";
  update();
  return true;
}

void LedRuler::paint(QPainter *painter){

    painter->drawPixmap(0, 0, m_map);
    painter->rotate(m_rotation);
    painter->setBrush(m_color);
    painter->drawRect(m_pix_rect);
    qDebug() << "XXXXXXX";
}

void LedRuler::rulerUpdate(int x,int y){

    m_pix_rect.moveTo(x - m_pix_rect.height()/2, y - m_pix_rect.height()/2);
    m_part_map = m_map.copy(m_pix_rect);

    Interpolation::setLedColor(this);
    update(); 
}

void LedRuler::rulerUpdate(){ update(); }