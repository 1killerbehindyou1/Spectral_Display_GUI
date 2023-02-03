#include <gtest/gtest.h>
#include <Interpolator.h>
#include <QColor>

TEST(InterpolatorShould, shouldReturnEmptyColorWhenNoPixmapSet) {
    Interpolator interpolator{};

    QColor result = interpolator.interpolatorSetLedColor({});
    EXPECT_EQ(result, QColor{});
}
