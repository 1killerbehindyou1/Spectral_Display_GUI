#include "Transformation.hpp"

namespace common
{

Transform::Transform(const QPointF& rotCenter, double deg_angle)
    : m_rotCenter{rotCenter}, m_angle{deg_angle}
{
}

QPointF Transform::operator()(const QPointF& point) const
{
    /**
     * Translate point into local coordinates relative to rotation center.
     */
    const double dx = point.x() - m_rotCenter.x();
    const double dy = point.y() - m_rotCenter.y();

    /**
     * Precompute trigonometric values for current rotation angle.
     * This optimization avoids recalculating sin/cos for each point.
     */
    const double angle_rad = constants::degToRad(m_angle);
    const double cos_a = std::cos(angle_rad);
    const double sin_a = std::sin(angle_rad);

    /**
     * Rotate local vector and translate it back to global coordinates.
     */
    return {m_rotCenter.x() + dx * cos_a - dy * sin_a,
            m_rotCenter.y() + dx * sin_a + dy * cos_a};
}

QPolygonF Transform::operator()(const QRectF& rect) const
{
    /**
     * Rectangle always has 4 corners, reserve memory to avoid reallocations.
     */
    QPolygonF result;
    result.reserve(4);

    /**
     * Compute sin/cos once and reuse for all rectangle corners.
     */
    const double angle_rad = constants::degToRad(m_angle);
    const double cos_a = std::cos(angle_rad);
    const double sin_a = std::sin(angle_rad);

    /**
     * Local helper: rotate one point around m_rotCenter.
     */
    const auto rotate_point = [&](const QPointF& point) -> QPointF
    {
        const double dx = point.x() - m_rotCenter.x();
        const double dy = point.y() - m_rotCenter.y();
        return {m_rotCenter.x() + dx * cos_a - dy * sin_a,
                m_rotCenter.y() + dx * sin_a + dy * cos_a};
    };

    /**
     * Transform all rectangle corners in clockwise order.
     */
    result << rotate_point(rect.topLeft()) << rotate_point(rect.topRight())
           << rotate_point(rect.bottomRight())
           << rotate_point(rect.bottomLeft());

    return result;
}
} // namespace common
