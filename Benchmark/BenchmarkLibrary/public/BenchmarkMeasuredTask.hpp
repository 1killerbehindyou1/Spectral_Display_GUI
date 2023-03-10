#ifndef BENCHMARK_MEASURED_TASK_H
#define BENCHMARK_MEASURED_TASK_H

#include <QImage>
#include <string>

QImage interpolatorMeasurement(int led_number, int led_size, int angle,
                               const std::string& pixmap_path);

#endif