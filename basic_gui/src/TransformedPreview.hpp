#pragma once

#include <QImage>
#include <QObject>
#include <QPainter>
#include <QtQuick/QQuickPaintedItem>

class TransformedPreview : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    TransformedPreview(QQuickItem* parent = 0);
    void paint(QPainter* painter) override;

    Q_INVOKABLE void ShowOutputPreview(bool show);

private:
    QImage* m_current_transformed_image = nullptr;
    bool m_rendered_preview;
};