
#include "LedRuler.h"
#include "Interpolation.h"
#include <iostream>
#include <QDebug>

LedRuler::LedRuler(QQuickItem *parent): QQuickPaintedItem(parent), m_number_of_leds(20),
           m_pix_rect(new QRect[m_number_of_leds]), m_color(new QColor[m_number_of_leds])
{
    int x = 0;
    int y = 0;
    for(int i =0; m_number_of_leds > i; i++)
    {
        m_pix_rect[i].setHeight(m_size);
        m_pix_rect[i].setWidth(m_size);
        m_pix_rect[i].moveTo(x, y);
        x += (m_size + m_spacing);
    }
    std::cout<< "LED Ruler constructor" << std::endl;
}

void LedRuler::setSize( const int &size)
{
    m_size = size;
    for(int i =0; m_number_of_leds > i; i++)
    {
        m_pix_rect[i].setHeight(size);
        m_pix_rect[i].setWidth(size);
    }
}

int LedRuler::size() const { return m_size ;}

int LedRuler::spacing() const { return m_spacing; }

void LedRuler::setSpacing(const int &spacing) { m_spacing = spacing; }

int LedRuler::number_of_leds() const { return m_number_of_leds; }

void LedRuler::setNumber_of_leds(const int &number_of_leds) { m_number_of_leds = number_of_leds; }

QPixmap LedRuler::getPixMap() const { return m_part_map;}

bool LedRuler::setPixMap(QUrl path){
    
  if (!path.isLocalFile()) {
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

  if (m_map.isNull()) {
    qDebug() << "Loaded file is null";
    return false;
  }
}

int LedRuler::step() const {return m_step; }

void LedRuler::setStep(const int &step) { m_step = step; }

void LedRuler::setPoint(const QPoint &point) {
    
    std::cout<< point.x() << " " << point.y();
     m_point = point; 
     rulerUpdate();
}

void LedRuler::paint(QPainter *painter)
{
    painter->drawPixmap(0,0,m_map);
    painter->translate(m_point);
    QColor color("white");

    for(int rot = 0; rot <= 360; rot += m_step){
        painter->rotate(rot);
        for(int i =0; m_number_of_leds > i; i++)
        {
            painter->setBrush(color/*m_color[i]*/);
            painter->drawRect(m_pix_rect[i]);
        }
    }
}

void LedRuler::rulerUpdate()
{
    int x = m_size *1.5;
    int y = m_size * 0.5;

    for(int i =0; m_number_of_leds > i; i++)
    {
        m_pix_rect[i].moveTo(x - m_size, y - m_size);
        m_part_map = m_map.copy(m_pix_rect[i]);

        m_color[i] = Interpolation::setLedColor(this);
        x += (m_spacing + m_size);
    }
    update();
}

