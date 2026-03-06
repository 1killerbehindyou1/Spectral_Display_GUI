#pragma once

#include <QPoint>
#include <QtQuick/QQuickPaintedItem>

class QPainter;

/**
 * @brief QML-exposed painted item used to visualize selection area.
 */
class RenderSelector : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    /**
     * @brief Constructs selector item.
     * @param parent Optional QQuickItem parent.
     */
    RenderSelector(QQuickItem* parent = nullptr);

    /**
     * @brief Paints selector overlay.
     * @param painter Active painter used by Qt scene graph.
     */
    void paint(QPainter* painter) override;

    /**
     * @brief Sets selector center point.
     * @param point New selector center in item coordinates.
     */
    Q_INVOKABLE void setPoint(QPoint point);

    /**
     * @brief Updates selector radius.
     * @param no_pixels New selector radius.
     */
    Q_INVOKABLE void selectorResize(int no_pixels);

private:
    QPoint m_point; // środek odrysowywania
    int m_radius;   // promień zaznaczenia
};