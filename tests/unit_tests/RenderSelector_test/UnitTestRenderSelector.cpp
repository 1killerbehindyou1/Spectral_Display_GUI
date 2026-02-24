#include <RenderSelector.hpp>
#include <gtest/gtest.h>

#include <QImage>
#include <QPainter>

namespace
{

QImage paintSelector(RenderSelector& selector)
{
    QImage image(900, 900, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    selector.paint(&painter);

    return image;
}

bool isWhite(const QColor& color)
{
    return color.red() == 255 && color.green() == 255 && color.blue() == 255;
}

TEST(RenderSelectorTest, defaultPaintColorsDefaultCenter)
{
    RenderSelector selector;

    const QImage image = paintSelector(selector);
    const QColor centerColor = image.pixelColor(400, 400);

    EXPECT_FALSE(isWhite(centerColor));
}

TEST(RenderSelectorTest, setPointMovesPaintedArea)
{
    RenderSelector selector;
    selector.selectorUpdate(1, 1);
    selector.setPoint(QPoint{100, 100});

    const QImage image = paintSelector(selector);

    EXPECT_FALSE(isWhite(image.pixelColor(100, 100)));
    EXPECT_TRUE(isWhite(image.pixelColor(400, 400)));
}

TEST(RenderSelectorTest, selectorUpdateChangesRadius)
{
    RenderSelector selector;
    selector.setPoint(QPoint{200, 200});

    selector.selectorUpdate(1, 1);
    const QImage imageSmall = paintSelector(selector);

    selector.selectorUpdate(20, 1);
    const QImage imageLarge = paintSelector(selector);

    EXPECT_TRUE(isWhite(imageSmall.pixelColor(210, 200)));
    EXPECT_FALSE(isWhite(imageLarge.pixelColor(210, 200)));
}

} // namespace
