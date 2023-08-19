#include <Constants.hpp>
#include <Transformation.hpp>

namespace common
{
Transform::Transform(const QPointF& rotCenter, float deg_angle)
    : m_rotCenter(rotCenter), m_angle(constants::degToRad(deg_angle))
{
}

QPointF Transform::operator()(const QPointF& point)
{

    QPointF new_point = point - m_rotCenter;
    std::complex<float> new_point_cpl(new_point.x(), new_point.y());

    float angle = std::arg(new_point_cpl);

    angle += new_point.y() < 0 ? constants::two_pi : 0;

    float module = std::abs(new_point_cpl);
    m_angle += angle;
    QPointF out_point{module * cos(m_angle), module * sin(m_angle)};
    out_point += m_rotCenter;
    m_angle -= angle;
    return out_point;
}

QRect Transform::operator()(const QRectF& rect)
{
    QPointF top_left = this->operator()(rect.topLeft());
    QPointF bottom_right = this->operator()(rect.bottomRight());
    return {top_left.toPoint(), bottom_right.toPoint()};
};

QPolygonF Transform::operator()(const QPolygonF& poly)
{
    QPolygonF result;
    for (const QPointF& p : poly)
    {
        result << Transform::operator()(p);
    }
    return result;
}
} // namespace common
