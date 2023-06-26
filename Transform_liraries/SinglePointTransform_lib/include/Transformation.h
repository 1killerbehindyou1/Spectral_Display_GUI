
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Constants.hpp>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QVector>
#include <cmath>


class Transform
{
public:
    Transform(const QPointF& rotCenter, float deg_angle);
    QPointF operator()(const QPointF& point);
    QRect operator()(const QRectF& rect);
    QPolygonF operator()(const QPolygonF& poly);

private:
    QPointF m_rotCenter;
    float m_angle;
};

#endif
