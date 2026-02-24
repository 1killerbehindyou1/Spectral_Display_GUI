#pragma once

#include <QtQuick/QQuickPaintedItem>
#include <QDebug>
#include <QObject>
#include <QPainter>
#include <QPixmap>

class OutputPreview : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QImage* image READ getImage WRITE setImage)

public:
    OutputPreview(QQuickItem* parent = 0);

    inline QImage* getImage() const
    {
        return m_current_transformed_image.get();
    }

    inline void setImage(QImage* image)
    {
        m_current_transformed_image = std::make_shared<QImage>(*image);
    }

public slots:
    void drawPreview(std::shared_ptr<QImage> last_image);

private:
    void paint(QPainter* painter) override;
    std::shared_ptr<QImage> m_current_transformed_image;
};
