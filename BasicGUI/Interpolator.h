
#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <cmath>

/**
 * @brief Instance of ColorColmponent Class represent single color component
 * in RGB image format.
 */
//////////////////////////////////////////////////////////////////
struct ColorComponent
{
    int iterator = 0;
    int sum = 0;
    int level = 0;
};

//////////////////////////////////////////////////////////////////
class Interpolator : public QObject
{
    Q_OBJECT

public:
    Interpolator(QObject* parent = 0);

    QColor interpolatorSetLedColor(QVector<QPointF> vector_points);
    QVector<QPointF> interpolatorTransform(QPoint sr_obr, QRect rect,
                                           float angle);

    QPixmap inerpolator_pixmap;

private:
    ColorComponent red_component;
    ColorComponent green_component;
    ColorComponent blue_component;
};
#endif
