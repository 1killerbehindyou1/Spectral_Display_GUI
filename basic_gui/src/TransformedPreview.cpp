
#include "TransformedPreview.hpp"

TransformedPreview::TransformedPreview(QQuickItem* parent)
                    : QQuickPaintedItem(parent)
{
    m_rendered_preview = false;
}

void TransformedPreview::paint(QPainter* painter)
{
    if (m_rendered_preview && m_current_transformed_image != nullptr)
    {
        painter->drawImage(QPoint{0, 700}, *m_current_transformed_image);
    }
    //painter->rotate(270);
    // from merged code
    //     painter->save();
    //     painter->translate(400, 400);
    //     painter->rotate(90);
    //     painter->drawImage(QPoint{0, 0}, *m_output_image);
    //     painter->restore();
    // }
    // painter->translate(m_center);
    // QPoint offset(m_size * 0.5, m_size * (-0.5));
    // QPoint pixel{0, 0};
}

void TransformedPreview::ShowOutputPreview(bool show)
{
    m_rendered_preview = show;
    update();
}