
#ifndef PIE_CHART_H
#define PIE_CHART_H

#include <QColor>
#include <QtQuick/QQuickPaintedItem>


class PieChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    //QML_ELEMENT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:

    PieChart(QQuickItem *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter);

    Q_INVOKABLE void clearChart();

signals:
    void colorChanged();

private:
    QString m_name;
    QColor m_color;
};



#endif

