#pragma once
#include <InterpolatorBase.hpp>

namespace single
{
class InterpolatorSingle : public common::InterpolatorBase
{
public:
    QColor interpolateColor(const QPolygonF& transformed_poly) override;
};
} // namespace single