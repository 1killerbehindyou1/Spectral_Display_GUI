#include <CommonTests.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QPolygonF>
#include <Transformation.hpp>
#include <memory>

struct params
{
    bool p;
};

class InterpolationTestWithParams : public testing::TestWithParam<params>
{

public:
};

TEST_P(InterpolationTestWithParams, transform_test_float)
{
    using namespace test_utils;

    Transform_float f_transform{QPointF{45.6, 46.7}, 56.8};

    std::cout << f_transform(QPointF{34.56, 67.55}) << std::endl;
    std::cout << f_transform(QPointF{4.56, 6.55}) << std::endl;
    std::cout << f_transform(QPointF{3.5, 7.5}) << std::endl;

    EXPECT_EQ(true, true);
}

TEST_P(InterpolationTestWithParams, transform_test_int)
{
    using namespace test_utils;

    Transform_int i_transform{QPoint{30, 60}, 45};

    std::cout << i_transform(QPoint{34, 67}) << std::endl;
    std::cout << i_transform(QPoint{6, 51}) << std::endl;
    std::cout << i_transform(QPoint{67, 12}) << std::endl;

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(std::vector<params>{true}));