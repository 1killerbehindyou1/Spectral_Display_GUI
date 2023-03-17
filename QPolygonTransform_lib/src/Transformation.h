
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
    QPointF operator()(const QPointF& point);

private:
    QPoint m_rotCenter;
    float m_angle;
};

#endif
