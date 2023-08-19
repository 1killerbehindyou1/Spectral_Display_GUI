#include "BenchmarkMeasuredTask.hpp"
#include <InterpolatorSingle.hpp>

QImage interpolatorMeasurement(int led_number, int led_size, int angle,
                               const std::string& pixmap_path)
{
    QPixmap pix_map{};
    pix_map.load(QString::fromStdString(pixmap_path));
    SniglePointlib::Interpolator interpolator_obj{};

    interpolator_obj.setPixmap(&pix_map);

    QImage output_image =
        interpolator_obj.transformImage(angle, led_size, led_number);

    return output_image;
}
