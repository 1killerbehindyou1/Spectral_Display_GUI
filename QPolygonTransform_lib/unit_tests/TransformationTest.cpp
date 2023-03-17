#include <QDebug>
#include <Transformation.h>
#include <gtest/gtest.h>

TEST(TransformTest, test_1)
{
    Transform transform{{0, 0}, 1};
    qDebug() << transform({1, 0});
    // EXPECT_EQ(out, comp);
}

TEST(TransformTest, test_2)
{
    Transform transform{{0, 0}, 0.5};
    qDebug() << transform({1, 0});
    // EXPECT_EQ(out, comp);
}

TEST(TransformTest, test_3)
{
    Transform transform{{0, 0}, 89.9};

    qDebug() << transform({1, 0});
    // QPointF comp{1, 1};
    // EXPECT_EQ(out, comp);
}
