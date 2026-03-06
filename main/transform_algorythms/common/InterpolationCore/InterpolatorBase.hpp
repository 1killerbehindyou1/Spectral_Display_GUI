#pragma once
#include <QPixmap>
#include <Transformation.hpp>

namespace common
{

/**
 * @brief Base interface for interpolation strategies used by transformation.
 */
class InterpolatorBase
{

public:
    /** @brief Virtual destructor for polymorphic usage. */
    virtual ~InterpolatorBase() = default;

    /**
     * @brief Computes representative color for transformed polygon area.
     * @param transformed_poly Polygon in source image coordinates.
     * @param pix_map Source pixmap.
     * @return Interpolated color.
     */
    virtual QColor interpolateColor(const QPolygonF& transformed_poly,
                                    const QPixmap* pix_map) = 0;

    /**
     * @brief Performs full transformation from source image to output image.
     * @param ang_resolution Angular resolution in degrees.
     * @param no_pixels Number of output pixels.
     * @param transform_center Transformation center.
     * @param pix_map Source pixmap.
     * @return Transformed image.
     */
    QImage transformImage(int ang_resolution, int no_pixels,
                          QPoint transform_center, const QPixmap* pix_map);
};
}; // namespace common
