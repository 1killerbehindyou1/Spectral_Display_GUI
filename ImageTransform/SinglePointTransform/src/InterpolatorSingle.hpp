#pragma once
#include <InterpolatorBase.hpp>

namespace single
{
class InterpolatorSingle : public common::InterpolatorBase
{
public:
    ~InterpolatorSingle() override = default;

    QColor interpolateColor(const QPolygonF& transformed_poly,
                            const QPixmap* pix_map) override;
};
} // namespace single