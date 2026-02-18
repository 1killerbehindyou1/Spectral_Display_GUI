#include "Transformation.hpp"

namespace common
{

Transform::Transform(const QPointF& rotCenter, double deg_angle)
    : m_rotCenter{rotCenter}, m_angle{deg_angle}
{
}

QPointF Transform::operator()(const QPointF& point) const
{
    QPointF point_f{point};
    QPointF new_point = point_f - m_rotCenter;
    std::complex<double> new_point_cpl(new_point.x(), new_point.y());

    double angle = std::arg(new_point_cpl);

    angle += new_point.y() < 0 ? constants::two_pi : 0;

    double module = std::abs(new_point_cpl);
    angle += m_angle;

    QPointF out_point{module * cos(m_angle), module * sin(m_angle)};
    out_point += m_rotCenter;

    return out_point;
}

QPolygonF Transform::operator()(const QRectF& rect) const
{
    QPolygonF result;
    QPolygonF polygon{rect};

    for (const QPointF& p : polygon)
    {
        result << (*this)(p);
    }
    return result;
}
} // namespace common
