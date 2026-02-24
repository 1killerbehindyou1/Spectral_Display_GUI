#include "OutputPreview.hpp"

OutputPreview::OutputPreview(QQuickItem* parent)
    : QQuickPaintedItem(parent), m_current_transformed_image(nullptr)
{
}

void OutputPreview::drawPreview(std::shared_ptr<QImage> last_image)
{
    if (last_image == nullptr || last_image->isNull())
    {
        qDebug() << "No image to draw.";
        return;
    }
    m_current_transformed_image = last_image;
    qDebug() << "Updateing preview with new image.";
    setImage(last_image.get());
    update();
}

void OutputPreview::paint(QPainter* painter)
{
    if (m_current_transformed_image != nullptr)
    {
        painter->drawImage(QPoint{0, 0}, *m_current_transformed_image);
    }
}