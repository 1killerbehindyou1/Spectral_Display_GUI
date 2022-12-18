
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
//////////////////////////////////////////////////////////////////
class ColorComponent
{

public:
    ColorComponent() : sum(0), level(0) {}

    void clearMembers()
    {
        int sum = 0;
        int level = 0;
    }

    void sumUpdate(int color) { sum += color; }

    void calculateColorIntensivity(int sample_amount)
    {
        level = sum / sample_amount;
    }

    int componentColorIntensivity() { return level; }

private:
    int sum;
    int level;
};

//////////////////////////////////////////////////////////////////
class Interpolator : public QObject
{
    Q_OBJECT

public:
    Interpolator(QObject* parent = 0);

    QColor interpolatorSetLedColor(QVector<QPointF> vector_points);
    QVector<QPointF> interpolatorTransform(Transform transform, QRect rect);
    QPixmap* inerpolator_pixmap;

private:
    ColorComponent red_component;
    ColorComponent green_component;
    ColorComponent blue_component;
};
#endif
