#include <LedRuler.hpp>
#include <gtest/gtest.h>

#include <QImage>
#include <QPainter>

namespace
{

QImage paintLedRuler(LedRuler& ruler)
{
    QImage image(900, 900, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    ruler.paint(&painter);

    return image;
}

bool isWhite(const QColor& color)
{
    return color.red() == 255 && color.green() == 255 && color.blue() == 255;
}

TEST(LedRulerTest, setAndGetPixmapReturnsSamePointer)
{
    LedRuler ruler;

    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::blue);

    ruler.setPixmap(&pixmap);

    EXPECT_EQ(ruler.pixmap(), &pixmap);
}

TEST(LedRulerTest, paintWithNoTransformedImageKeepsCanvasUntouched)
{
    LedRuler ruler;

    const QImage image = paintLedRuler(ruler);

    EXPECT_TRUE(isWhite(image.pixelColor(100, 100)));
    EXPECT_TRUE(isWhite(image.pixelColor(500, 500)));
}

TEST(LedRulerTest, onParameterChangedWithValidPixmapProducesRenderedPaint)
{
    LedRuler ruler;

    QImage sourceImage(64, 64, QImage::Format_RGB32);
    sourceImage.fill(Qt::red);
    QPixmap pixmap = QPixmap::fromImage(sourceImage);
    ruler.setPixmap(&pixmap);

    ruler.onParameterChanged(10, 45, 2);

    const QImage image = paintLedRuler(ruler);

    EXPECT_FALSE(isWhite(image.pixelColor(250, 250)));
}

TEST(LedRulerTest, setPointTriggersTransformationWhenPixmapIsPresent)
{
    LedRuler ruler;

    QImage sourceImage(64, 64, QImage::Format_RGB32);
    sourceImage.fill(Qt::green);
    QPixmap pixmap = QPixmap::fromImage(sourceImage);
    ruler.setPixmap(&pixmap);

    ruler.onParameterChanged(8, 30, 2);
    ruler.setPoint(QPoint{30, 30});

    const QImage image = paintLedRuler(ruler);

    EXPECT_FALSE(isWhite(image.pixelColor(250, 250)));
}

TEST(LedRulerTest, getRenderedImageDefaultsToNullptr)
{
    LedRuler ruler;

    EXPECT_EQ(ruler.getRenderedImage(), nullptr);
}

} // namespace
