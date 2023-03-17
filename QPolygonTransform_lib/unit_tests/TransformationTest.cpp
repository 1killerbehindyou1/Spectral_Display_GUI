#include <Transformation.h>
#include <gtest/gtest.h>

TEST(TransformTest, test_1)
{
    int a = 1;
    Transform transform{QPointF{}, a};
    QPointF out = transform({1, 1});
    EXPECT_EQ(out, QPointF{1, 1});
}
