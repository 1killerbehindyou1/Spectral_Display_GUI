#include <LiveImageProvider.hpp>

#include <gtest/gtest.h>

#include <QImage>

namespace
{

bool hasPixelColor(const QImage& image, int x, int y, const QColor& color)
{
    return image.pixelColor(x, y) == color;
}

TEST(OutputPreviewTest, defaultImageIsNull)
{
    LiveImageProvider preview;

    EXPECT_TRUE(preview.image().isNull());
}

TEST(OutputPreviewTest, setImageStoresCopy)
{
    LiveImageProvider preview;

    QImage input(6, 6, QImage::Format_RGB32);
    input.fill(Qt::black);

    preview.setImage(input);
    const QImage& stored = preview.image();

    EXPECT_NE(&stored, &input);
    EXPECT_TRUE(hasPixelColor(stored, 0, 0, Qt::black));

    input.fill(Qt::white);
    EXPECT_TRUE(hasPixelColor(stored, 0, 0, Qt::black));
}

TEST(OutputPreviewTest, drawPreviewSetsImageFromSharedPtr)
{
    LiveImageProvider preview;

    QImage transformed(6, 6, QImage::Format_RGB32);
    transformed.fill(Qt::black);
    preview.setImage(transformed);

    const QImage& stored = preview.image();
    EXPECT_TRUE(hasPixelColor(stored, 0, 0, Qt::black));
}

TEST(OutputPreviewTest, drawPreviewIgnoresNullImage)
{
    LiveImageProvider preview;

    EXPECT_TRUE(preview.image().isNull());
}

} // namespace
