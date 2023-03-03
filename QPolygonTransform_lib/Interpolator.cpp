
#include "Interpolator.h"
#include <QDebug>
#include <cmath>
#include <iostream>

namespace
{

QColor operator+=(QColor& color_a, const QColor& color_b)
{
    color_a.setRedF(color_a.redF() + color_b.redF());
    color_a.setGreenF(color_a.greenF() + color_b.greenF());
    color_a.setBlueF(color_a.blueF() + color_b.blueF());

    return color_a;
}

QColor operator/(const QColor& total_intensivity, int sample_amount)
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
                led_color += image.pixelColor(point.x(), point.y());
            }
            else
            {
                return {};
            }
        }
        return led_color / vector_points.size();
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
    transformed_poly << transform(rect.topLeft())
                     << transform(rect.bottomLeft())
                     << transform(rect.bottomRight())
                     << transform(rect.topRight());

    QPointF curr_point{};
    QVector<QPointF> vector_points{};
    QRectF rect_f{transformed_poly.boundingRect()};

    for (float y = 0; y < rect_f.height(); y++)
    {
        curr_point.setY(rect_f.topLeft().y() + y);

        for (float x = 0; x < rect_f.width(); x++)
        {
            curr_point.setX(rect_f.topLeft().x() + x);

            if ((curr_point.x() >= 0) && (curr_point.y() >= 0) &&
                (transformed_poly.containsPoint(curr_point, Qt::OddEvenFill)))
                vector_points.push_front(curr_point);
        }
    }
    /*qDebug() << "boundingRect dimensions: " << rect_f.height()
             << rect_f.width();
    qDebug() << "boundingRect pointss: " << rect_f.height() * rect_f.width();
    qDebug() << "points: " << vector_points.size() << "\n";*/
    return vector_points;
}

///////////////////////////////////////////////////////////////////q
