#pragma once
#include <InterpolatorBase.hpp>

namespace poly
{
/**
 * @brief Interpolator that samples color using polygon-area strategy.
 */
class InterpolatorQPoly : public common::InterpolatorBase
{
public:
    /** @brief Virtual destructor. */
    ~InterpolatorQPoly() override = default;

    /**
     * @brief Computes color for transformed polygon using polygon strategy.
     * @param transformed_poly Transformed polygon area.
     * @param pix_map Source pixmap.
     * @return Interpolated color.
     */
    QColor interpolateColor(const QPolygonF& transformed_poly,
                            const QPixmap* pix_map) override;
};
} // namespace poly