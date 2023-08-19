#pragma once

#include <QImage>
#include <string>

QImage interpolatorMeasurement(int led_number, int led_size, int angle,
                               const std::string& pixmap_path);
