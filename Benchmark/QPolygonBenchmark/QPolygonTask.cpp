#include "QPolygonTask.hpp"
#include "../../QPolygonTransform_lib/Interpolator.h"

void interpolatorMeasurement(int led_number, int led_size, int angle,
                             const std::string& pixmap_path)
{
    QPixmap pix_map{};
    pix_map.load(QString::fromStdString(pixmap_path));
    Interpolator interpolator_obj{};

    interpolator_obj.setPixmap(&pix_map);

    QPoint rot_centr(pix_map.width() / 2, pix_map.height() / 2);

    QRect rect{QPoint{static_cast<int>(led_size * 0.5),
                      static_cast<int>(led_size * (-0.5))},
               QSize{led_size, led_size}};

    for (int rot = 0; rot < 360; rot += angle)
    {
        for (int i = 0; i < led_number; i++)
        {
            rect.moveTo(rect.topLeft() + QPoint{led_size, 0});

            QColor color = interpolator_obj.interpolatorSetLedColor(
                interpolator_obj.interpolatorTransform(
                    Transform{rot_centr, angle}, rect));
        }
    }
}
