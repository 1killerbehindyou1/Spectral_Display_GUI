
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>

struct Transform
{

    float static calcModule(QPointF point, float angle);
    float static calcAngle(QPointF point);
    float static convertAngleToRad(float deg_angle);
    float static updateAngle(float ext_angle, float angle);
    QPointF static updatePoint(QPointF center_of_rot, QPointF point,
                               float module, float angle);
};

#endif
