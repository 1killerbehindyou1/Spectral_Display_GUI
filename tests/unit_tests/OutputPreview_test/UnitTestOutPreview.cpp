#include <OutputPreview.hpp>

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
    OutputPreview preview;

    EXPECT_EQ(preview.getImage(), nullptr);
}

TEST(OutputPreviewTest, setImageStoresCopy)
{
    OutputPreview preview;

    QImage input(6, 6, QImage::Format_RGB32);
    input.fill(Qt::black);

    preview.setImage(&input);
    QImage* stored = preview.getImage();

    ASSERT_NE(stored, nullptr);
    EXPECT_NE(stored, &input);
    EXPECT_TRUE(hasPixelColor(*stored, 0, 0, Qt::black));

    input.fill(Qt::white);
    EXPECT_TRUE(hasPixelColor(*stored, 0, 0, Qt::black));
}

TEST(OutputPreviewTest, drawPreviewSetsImageFromSharedPtr)
{
    OutputPreview preview;

    auto transformed = std::make_shared<QImage>(6, 6, QImage::Format_RGB32);
    transformed->fill(Qt::black);

    preview.drawPreview(transformed);

    QImage* stored = preview.getImage();
    ASSERT_NE(stored, nullptr);
    EXPECT_TRUE(hasPixelColor(*stored, 0, 0, Qt::black));
}

TEST(OutputPreviewTest, drawPreviewIgnoresNullImage)
{
    OutputPreview preview;

    preview.drawPreview(nullptr);

    EXPECT_EQ(preview.getImage(), nullptr);
}

} // namespace
