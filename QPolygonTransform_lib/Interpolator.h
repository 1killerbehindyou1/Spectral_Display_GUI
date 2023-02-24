
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

    QColor interpolatorSetLedColor(const QVector<QPointF>& vect);
    QVector<QPointF> interpolatorTransform(Transform transform,
                                           const QRect& rect);
    void setPixmap(QPixmap* pixmap);

private:
    QPixmap* inerpolator_pixmap;
};

namespace
{
void increaseTotalIntensivity(QColor& color, const QColor& color_from_image);
QColor calculateaAverageIntensivity(int sample_amount,
                                    const QColor& total_intensivity);
} // namespace

#endif
