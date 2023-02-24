
#include "Interpolator.h"
#include <QDebug>
#include <cmath>
#include <iostream>

Interpolator::Interpolator(QObject* parent)
    : QObject(parent), inerpolator_pixmap(nullptr)
{
}
void Interpolator::setPixmap(QPixmap* pixmap) { inerpolator_pixmap = pixmap; }

QColor
Interpolator::interpolatorSetLedColor(const QVector<QPointF>& vector_points)
{

    if ((inerpolator_pixmap != nullptr) && (vector_points.size() > 0))
    {
        QColor led_color{};
        QImage image{inerpolator_pixmap->toImage()};

        for (QPointF point : vector_points)
        {
            if (point.x() < image.width() && point.y() < image.height())
            {
                increaseTotalIntensivity(
                    led_color, image.pixelColor(point.x(), point.y()));
            }
            else
            {
                return {}; // increaseTotalIntensivity(led_color, QColor{0, 0,
                           // 0});
            }
        }

        return calculateaAverageIntensivity(vector_points.size(), led_color);
    }

    else
    {
        return {};
    }
}
//////////////////////////////////////////////////////////////////

QVector<QPointF> Interpolator::interpolatorTransform(Transform transform,
                                                     const QRect& rect)
{

    QPolygonF transformed_poly; // poligon with transformed points
    transformed_poly << transform(rect.topLeft()) << transform(rect.topRight())
                     << transform(rect.bottomLeft())
                     << transform(rect.bottomRight());

    QPointF curr_point{};
    QVector<QPointF> vector_points{};
    QRectF rect_f{transformed_poly.boundingRect()};

    for (float y = 0; y < rect_f.height(); y += 0.1)
    {
        curr_point.setY(rect_f.topLeft().y() + y);

        for (float x = 0; x < rect_f.width(); x += 0.1)
        {
            curr_point.setX(rect_f.topLeft().x() + x);

            if (curr_point.x() >= 0 && curr_point.y() >= 0 &&
                transformed_poly.containsPoint(curr_point, Qt::WindingFill))
                vector_points.push_front(curr_point);
        }
    }
    return vector_points;
}

///////////////////////////////////////////////////////////////////q
namespace
{
void increaseTotalIntensivity(QColor& color, const QColor& color_from_image)
{

    color.setRedF(color.redF() + color_from_image.redF());
    color.setGreenF(color.greenF() + color_from_image.greenF());
    color.setBlueF(color.blueF() + color_from_image.blueF());
}

QColor calculateaAverageIntensivity(int sample_amount,
                                    const QColor& total_intensivity)
{
    QColor color;
    if (sample_amount > 0)
    {
        color.setRedF(total_intensivity.redF() / sample_amount);
        color.setGreenF(total_intensivity.greenF() / sample_amount);
        color.setBlueF(total_intensivity.blueF() / sample_amount);
        // color.setAlpha(0.6);
    }
    // qDebug() << color;
    return color;
}
} // namespace
