#include <BenchmarkMeasuredTask.hpp>
#include <InterpolatorQPoly.hpp>
#include <QDebug>
#include <string>

QImage interpolatorMeasurement(int led_number, int led_size, int angle,
                               const std::string& pixmap_path)
{
    QPixmap pix_map{};
    pix_map.load(QString::fromStdString(pixmap_path));
    poly::InterpolatorQPoly interpolator_obj{};

    QImage output_image =
        interpolator_obj.transformImage(angle, led_size, led_number, &pix_map);

    return output_image;
}
