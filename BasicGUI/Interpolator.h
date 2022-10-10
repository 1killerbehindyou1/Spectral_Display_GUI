
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QColor>
#include <QPoint>
#include <QVector>
#include <QPixmap>
#include <cmath>



class PointInReferenceSystem{

public:
    void calcModule();
    void calcAngle();
    void calcPoint();

    float module =0;
    float angle =0;
    QPoint point;
};


struct Component{

    int iterator =0;
    int sum =0;
    int level =0;
};

class Interpolator  : public QObject{
   
    Q_OBJECT

public:
    Interpolator(QObject* parent =0);

    QColor interpolatorSetLedColor(QVector<QPoint> vector_points);
    QVector<QPoint> interpolatorTransform(QPoint sr_obr, QRect rect, int angle);

    void degreeToRad(int angle);

    QPixmap inerpolator_pixmap;
    float m_angle;

private:
    Component red_component;
    Component green_component;
    Component blue_component;
};
#endif

