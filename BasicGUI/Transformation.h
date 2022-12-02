
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>

class Transform
{
public:
    Transform(QPoint rotCenter, float deg_angle);
    QPointF transformFrom(QPointF point);
    QPointF operator()(QPointF point);

private:
    float static calcModule(QPointF point, float angle);
    float static calcAngle(QPointF point);
    float static convertAngleToRad(float deg_angle);
    float static updateAngle(float ext_angle, float angle);

    QPointF static transformPoint(QPointF point, QPointF rotCenter,
                                  float module, float angle);
    QPoint m_rotCenter;
    float m_angle;
};

#endif
