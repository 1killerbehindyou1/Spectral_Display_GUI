
#include "LedRuler.h"
#include "Interpolator.h"
#include "ImageViewer.h"
#include <iostream>
#include <QDebug>
#include <QPen>

LedRuler::LedRuler(QQuickItem *parent)
                : QQuickPaintedItem(parent), m_number_of_leds(10){

    m_pixmap.load("C:\\Users\\mplesniak\\Desktop\\1. Mentoring_QT_project\\Spectral_Display_GUI\\Pictures\\BITMAPA.png");
}

void LedRuler::setSize( const int &size){ m_size = size; }

int LedRuler::size() const { return m_size ;}

int LedRuler::spacing() const { return m_spacing; }

void LedRuler::setSpacing(const int &spacing) { m_spacing = spacing; }

int LedRuler::number_of_leds() const { return m_number_of_leds; }

void LedRuler::setNumber_of_leds(const int &number_of_leds) { m_number_of_leds = number_of_leds; }

int LedRuler::step() const {return m_step; }

void LedRuler::setStep(const int &step) { m_step = step; }

void LedRuler::setPoint(const QPoint &point) {
    
     m_point = point; 
     rulerUpdate();
}

void LedRuler::paint(QPainter *painter)
{
    LedRuler::m_projection = new (QVector<QColor *>); 

    painter->translate(m_point);
    QPoint offset(m_size * 0.5, m_size *(-0.5));
    QColor color;

    for(int rot = 0; rot < 360; rot += m_step){ 
        
        QColor single_line[m_number_of_leds];       
        QRect rect{offset, QSize {m_size, m_size}};
        painter->save();
        painter->rotate(rot);
        
        for(int i =0; i < m_number_of_leds ; i++)
        {

            rect.moveTo(rect.topLeft() + QPoint{m_spacing + m_size, 0});
            color =Interpolation::setLedColor(Interpolation::transform(m_point, rect, rot),m_pixmap); 
            
            if(m_acquire_data_flag == true){
                single_line[i] = color;
            }

            QPen pen = painter->pen();
            pen.setColor(Qt::transparent);
            painter->setPen(pen);
            painter->setBrush(color);
            painter->drawRect(rect);
        }

        if(m_acquire_data_flag == true){
            LedRuler::m_projection->push_front(single_line);
           // std::cout<< "wielkosc wektora:  "<< LedRuler::m_projection->size()<<  std::endl;
        }
        painter->restore();
    }
     
    emit acquisitionFinished();
}

void LedRuler::rulerUpdate(){ update(); }

void LedRuler::onBitMapLoadedCorrectly(QPixmap pixmap) {m_pixmap = pixmap;}

void LedRuler::setAcquire(bool set){ m_acquire_data_flag = set; }

QVector<QColor *>* LedRuler::m_projection = nullptr;
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