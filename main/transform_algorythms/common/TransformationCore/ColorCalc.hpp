#pragma once

#include <QColor>

namespace common
{

/**
 * @brief Divides accumulated color channels by sample count.
 * @param total_intensivity Accumulated color value.
 * @param sample_amount Number of samples.
 * @return Averaged color.
 */
QColor operator/(const QColor& total_intensivity, int sample_amount);
/**
 * @brief Adds color channels from @p color_b into @p color_a.
 * @param color_a Accumulator color.
 * @param color_b Color to add.
 * @return Updated accumulator color.
 */
QColor operator+=(QColor& color_a, const QColor& color_b);

} // namespace common
