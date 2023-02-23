
#include "Interpolator.h"
#include <QDebug>
#include <cmath>
#include <iostream>

//////////////////////////////////////////////////////////////////
Interpolator::Interpolator(QObject* parent)
    : QObject(parent), inerpolator_pixmap(nullptr)
{
}
void Interpolator::setPixmap(QPixmap* pixmap) { inerpolator_pixmap = pixmap; }
//////////////////////////////////////////////////////////////////
QColor Interpolator::interpolatorSetLedColor(QVector<QPointF> vector_points)
{
    QColor led_color{};
    QImage image{};

    if (inerpolator_pixmap != nullptr)
        image = inerpolator_pixmap->toImage();
    else
        return led_color;

    for (QPointF point : vector_points)
    {
        if (point.x() < image.width() && point.y() < image.height())
        {

            increaseTotalIntensivity(
                led_color, image.pixelColor(static_cast<int>(point.x()),
                                            static_cast<int>(point.y())));
        }
        else
        {
            increaseTotalIntensivity(led_color, QColor{0, 0, 0});
        }
    }

    int rect_size = vector_points.size();

    if (rect_size > 0)
    {
        return led_color = calculateaAverageIntensivity(rect_size, led_color);
    }
    else
    {
        QColor color{};
        return color;
    }
}
//////////////////////////////////////////////////////////////////

QVector<QPointF> Interpolator::interpolatorTransform(Transform transform,
                                                     QRect rect)
{
    QVector<QPointF> vector_points{};
    QPointF curr_point{};

    QPolygonF transformed_poly{};

    QVector<QPointF> poly_points{rect.topLeft(), rect.topRight(),
                                 rect.bottomLeft(), rect.bottomRight()};

    for (auto point : poly_points)
    {
        transformed_poly << transform(point);
    }

    QRectF rect_f{transformed_poly.boundingRect()};

    for (float y = 0; y < rect_f.height(); y++)
    {
        curr_point.setY(rect_f.topLeft().y() + y);

        for (float x = 0; x < rect_f.width(); x++)
        {
            curr_point.setX(rect_f.topLeft().x() + x);

            if (curr_point.x() >= 0 && curr_point.y() >= 0 &&
                transformed_poly.containsPoint(curr_point, Qt::OddEvenFill))
                vector_points.push_front(curr_point);
        }
    }
    qDebug() << vector_points.size();
    return vector_points;
}

///////////////////////////////////////////////////////////////////q
namespace
{
void increaseTotalIntensivity(QColor& color, QColor color_from_image)
{

    color.setRedF(color.redF() + color_from_image.redF());
    color.setGreenF(color.greenF() + color_from_image.greenF());
    color.setBlueF(color.blueF() + color_from_image.blueF());
}

QColor calculateaAverageIntensivity(int sample_amount, QColor total_intensivity)
{
    QColor color;
    if (sample_amount > 0)
    {
        color.setRedF(total_intensivity.redF() / sample_amount);
        color.setGreenF(total_intensivity.greenF() / sample_amount);
        color.setBlueF(total_intensivity.blueF() / sample_amount);
    }

    return color;
}
} // namespace
