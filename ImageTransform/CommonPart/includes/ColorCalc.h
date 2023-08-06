#pragma once

#include <QColor>

namespace common
{

QColor operator/(const QColor& total_intensivity, int sample_amount);
QColor operator+=(QColor& color_a, const QColor& color_b);

} // namespace common
