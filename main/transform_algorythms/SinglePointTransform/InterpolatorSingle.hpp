#pragma once
#include <InterpolatorBase.hpp>

namespace single
{
/**
 * @brief Interpolator that samples color using single-point strategy.
 */
class InterpolatorSingle : public common::InterpolatorBase
{
public:
    /** @brief Virtual destructor. */
    ~InterpolatorSingle() override = default;

    /**
     * @brief Computes color for transformed polygon using single-point method.
     * @param transformed_poly Transformed polygon area.
     * @param pix_map Source pixmap.
     * @return Interpolated color.
     */
    QColor interpolateColor(const QPolygonF& transformed_poly,
                            const QPixmap* pix_map) override;
};
} // namespace single