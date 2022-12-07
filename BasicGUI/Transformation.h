
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
    QPoint m_rotCenter;
    float m_angle;
};

//////////////////////////////////////////////////////////////////
namespace
{
float calcModule(QPointF point, float angle);
float calcAngle(QPointF point);
float convertAngleToRad(float deg_angle);
float updateAngle(float ext_angle, float angle);
QPointF transformPoint(QPointF point, QPointF rotCenter, float module,
                       float angle);
} // namespace

#endif
