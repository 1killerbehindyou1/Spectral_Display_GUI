#include "../src/Interpolator.h"
#include <QColor>
#include <gtest/gtest.h>


TEST(InterpolatorShould, shouldReturnEmptyColorWhenNoPixmapSet)
{
    Interpolator interpolator{};

    QColor result = interpolator.interpolatorSetLedColor({});
    EXPECT_EQ(result, QColor{});
}
