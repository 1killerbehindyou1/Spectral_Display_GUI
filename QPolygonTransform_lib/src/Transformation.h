
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QVector>
#include <cmath>

namespace QPolyLib
{

constexpr double pi = 3.141592653589793238462643383279502884197169399375L;
constexpr double two_pi = 2 * pi;
constexpr double inv_pi = 1 / pi;
constexpr inline double degToRad(float deg) { return deg * pi / 180; }

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
} // namespace QPolyLib
#endif