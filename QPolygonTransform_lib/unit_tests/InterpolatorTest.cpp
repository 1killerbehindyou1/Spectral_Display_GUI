#include <Interpolator.h>
#include <gtest/gtest.h>

TEST(InterpolatorShould, shouldReturnEmptyColorWhenNoPixmapSet)
{
    Interpolator interpolator{};
    Transform transform{QPoint{}, 0};
    QRect rect{};
    QColor result = interpolator.interpolateColor(transform, rect);
    EXPECT_EQ(result, QColor{});
}