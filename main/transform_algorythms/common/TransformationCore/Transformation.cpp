#include "Transformation.hpp"

namespace common
{

Transform::Transform(const QPointF& rotCenter, double deg_angle)
    : m_rotCenter{rotCenter}, m_angle{deg_angle}
{
}

QPointF Transform::operator()(const QPointF& point) const
{
    const double dx = point.x() - m_rotCenter.x();
    const double dy = point.y() - m_rotCenter.y();

    const double angle_rad = constants::degToRad(m_angle);
    const double cos_a = std::cos(angle_rad);
    const double sin_a = std::sin(angle_rad);

    return {m_rotCenter.x() + dx * cos_a - dy * sin_a,
            m_rotCenter.y() + dx * sin_a + dy * cos_a};
}

QPolygonF Transform::operator()(const QRectF& rect) const
{
    QPolygonF result;
    result.reserve(4);

    const double angle_rad = constants::degToRad(m_angle);
    const double cos_a = std::cos(angle_rad);
    const double sin_a = std::sin(angle_rad);

    const auto rotate_point = [&](const QPointF& point) -> QPointF
    {
        const double dx = point.x() - m_rotCenter.x();
        const double dy = point.y() - m_rotCenter.y();
        return {m_rotCenter.x() + dx * cos_a - dy * sin_a,
                m_rotCenter.y() + dx * sin_a + dy * cos_a};
    };

    result << rotate_point(rect.topLeft()) << rotate_point(rect.topRight())
           << rotate_point(rect.bottomRight())
           << rotate_point(rect.bottomLeft());

    return result;
}
} // namespace common
