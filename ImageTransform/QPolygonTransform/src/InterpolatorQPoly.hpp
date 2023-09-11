#pragma once
#include <InterpolatorBase.hpp>

namespace poly
{
class InterpolatorQPoly : public common::InterpolatorBase
{
public:
    QColor interpolateColor(const QPolygonF& transformed_poly) override;
};
} // namespace poly