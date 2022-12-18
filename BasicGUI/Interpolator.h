
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "Transformation.h"
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>

/**
 * @brief Instance of ColorColmponent Class represent single color component
 * in RGB image format.
 */

class Interpolator : public QObject
{
    Q_OBJECT

public:
    Interpolator(QObject* parent = 0);

    QColor interpolatorSetLedColor(QVector<QPointF> vector_points);
    QVector<QPointF> interpolatorTransform(Transform transform, QRect rect);
    QPixmap* inerpolator_pixmap;
};

namespace
{
void increaseTotalInensivity(QColor& color, QColor color_from_image);
QColor calculateaAverageIntensivity(int sample_amount,
                                    QColor total_intensivity);
} // namespace

#endif
