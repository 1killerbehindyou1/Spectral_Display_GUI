#ifndef POLYGON_TASK_H
#define POLYGON_TASK_H

#include "../../QPolygonTransform_lib/Interpolator.h"
#include <string>

namespace polygon
{
void interpolatorMeasurement(int led_number, int led_size, int angle,
                             const std::string& pixmap_path);

} // namespace polygon
#endif