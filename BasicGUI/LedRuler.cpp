
#include "LedRuler.h"
#include "Interpolation.h"
#include <iostream>
#include <QDebug>

LedRuler::LedRuler(QQuickItem *parent): QQuickPaintedItem(parent), m_number_of_leds(10),
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
  emit fileErrLoad("ddd","SSS");
  rulerUpdate();
  return true;
}

int LedRuler::step() const {return m_step; }

void LedRuler::setStep(const int &step) { m_step = step; }

void LedRuler::setPoint(const QPoint &point) {
    
     m_point = point; 
     rulerUpdate();
}

void LedRuler::paint(QPainter *painter)
{
    painter->drawPixmap(0,0,m_map);
    painter->translate(m_point);
    
    QPoint offset(m_size * 0.5, m_size *(-0.5));
    QColor color;

    for(int rot = 0; rot < 360; rot += m_step){
        
        QRect rect{offset, QSize {m_size, m_size}};
        painter->save();
        painter->rotate(rot);
        
        for(int i =0; i < m_number_of_leds ; i++)
        {
            m_part_map = m_map.copy(rect);
            color = Interpolation::setLedColor(this);
            painter->setBrush(color);
            painter->drawRect(rect);
            rect.moveTo(rect.topLeft() + QPoint{m_spacing + m_size, 0});
           
        }
        painter->restore();
    }
}

void LedRuler::rulerUpdate()
{
    update();
}
    
/*
namespace {
void drawArm(QPainter* painter, double length, int ledCount)
{

    painter->save();
    auto pen = painter->pen();
    pen.setStyle(Qt::PenStyle::DashLine);
    pen.setColor(QColor::fromRgb(0, 0, 0, 130));
    painter->setPen(pen);

    painter->drawLine(QPointF { 0, 0 }, QPointF { 0, -length });
    painter->restore();

    if (ledCount <= 0)
        return;

    uint32_t uLedCount = ledCount;
    double ledOffset = length / ledCount;
    double firstLed = ledOffset / 2.0;

    QRectF firstLedRect = QRectF { QPointF {}, QSizeF { ledOffset * 0.5, ledOffset - 4 } };
    firstLedRect.moveCenter(QPointF { 0, ledOffset * -0.5 });
    auto ledRect = firstLedRect;

    painter->save();
    pen = painter->pen();
    pen.setColor(Qt::transparent);
    painter->setPen(pen);
    auto brush = painter->brush();
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(255, 255, 255, 130));
    painter->setBrush(brush);

    for (uint32_t ledIdx = 0; ledIdx < uLedCount; ++ledIdx, ledRect.translate(0, -ledOffset)) {
        painter->drawRoundedRect(ledRect, 2, 2);
    }

    painter->restore();
}
}

SpectralDisplayView::SpectralDisplayView()
    : rotationStepCount { 1 }
    , ledCount { 4 }
{
}

void SpectralDisplayView::paint(QPainter* painter)
{
    painter->save();
    auto currentSize = this->size();
    auto minSize = std::min(this->size().height(), this->size().width());
    auto rectSize = QSizeF { minSize, minSize } - QSizeF(1, 1);

    auto elipseCoords = QRectF { {}, rectSize };
    auto center = QRectF { {}, currentSize }.center();
    elipseCoords.moveCenter(center);
    painter->drawEllipse(elipseCoords);

    painter->translate(center);

    if (rotationStepCount > 0) {
        auto angleDelta = 360.0 / rotationStepCount;

        for (std::size_t armIdx = 0; armIdx < rotationStepCount; ++armIdx) {
            painter->save();
            painter->rotate(angleDelta * armIdx);

            drawArm(painter, minSize / 2.0, ledCount);

            painter->restore();
        }
    }

    painter->restore();
}
*/