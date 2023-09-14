
// #include <QDebug>
// #include <Transformation.hpp>

// TEST_P(InterpolationTestWithParams, transform_test_float)
// {
//     Transform_float f_transform{QPointF{45.6, 46.7}, 56.8};

//     QDebug() << f_transform(QPointF{34.56, 67.55}) << std::endl;
//     std::cout << f_transform(QPointF{4.56, 6.55}) << std::endl;
//     std::cout << f_transform(QPointF{3.5, 7.5}) << std::endl;

//     EXPECT_EQ(true, true);
// }

// TEST_P(InterpolationTestWithParams, transform_test_int)
// {
//     Transform_int i_transform{QPoint{30, 60}, 45};

//     std::cout << i_transform(QPoint{34, 67}) << std::endl;
//     std::cout << i_transform(QPoint{6, 51}) << std::endl;
//     std::cout << i_transform(QPoint{67, 12}) << std::endl;

//     EXPECT_EQ(true, true);
// }

// INSTANTIATE_TEST_SUITE_P(StandardTransformations,
// InterpolationTestWithParams,
//                          testing::ValuesIn(std::vector<params>{true}));

#include <Transformation.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct TransformationParams
{
    QPoint rotationCenter;
    float rotationAngle;
    QPointF inputPoint;
    QPointF expectedResult;
    double precision = 1e-5;
};

class TransformationTestWithParams
    : public testing::TestWithParam<TransformationParams>
{
};
class TransformationTestWithParamsCyclic
    : public testing::TestWithParam<TransformationParams>
{
};

TEST_P(TransformationTestWithParams, properlyTransformPoint)
{

    const auto& params = GetParam();

    common::Transform_float transform{params.rotationCenter,
                                      params.rotationAngle};
    QPointF point_out = transform(params.inputPoint);

    EXPECT_NEAR(params.expectedResult.x(), point_out.x(), params.precision);
    EXPECT_NEAR(params.expectedResult.y(), point_out.y(), params.precision);
}

TEST_P(TransformationTestWithParamsCyclic, verifyCyclicTransforamtion)
{
    const auto& params = GetParam();

    common::Transform_float transform{params.rotationCenter,
                                      params.rotationAngle};
    QPointF point_in{params.inputPoint};

    for (int i = 0; i <= 360 - params.rotationAngle; i += params.rotationAngle)
    {
        point_in = transform(point_in);
    }
    EXPECT_NEAR(params.expectedResult.x(), point_in.x(), params.precision);
    EXPECT_NEAR(params.expectedResult.y(), point_in.y(), params.precision);
}

std::vector<TransformationParams> transformationParams_cyclic{
    {{0, 0}, 90, {1, 1}, {1, 1}, 1e-3},
    {{0, 0}, 30, {1, 1}, {1, 1}, 1e-2},
    {{0, 0}, 10, {1, 1}, {1, 1}, 1e-2},
    {{0, 0}, 1, {1, 1}, {1, 1}, 1e-3},
    //
    {{0, 0}, 90, {5, 5}, {5, 5}, 1e-3},
    {{0, 0}, 30, {5, 5}, {5, 5}, 1e-3},
    {{0, 0}, 10, {5, 5}, {5, 5}, 1e-3},
    {{0, 0}, 1, {5, 5}, {5, 5}, 1e-3},
    {{10, 10}, 90, {5, 5}, {5, 5}, 1e-3},
    {{10, 10}, 30, {5, 5}, {5, 5}, 1e-3},
    {{10, 10}, 10, {5, 5}, {5, 5}, 1e-4},
    {{10, 10}, 1, {5, 5}, {5, 5}, 1e-3},
};

std::vector<TransformationParams> transformationParams{
    {{0, 0}, 0, {4, 4}, {4, 4}, 1e-5},
    {{0, 0}, 90, {4, 4}, {-4, 4}, 1e-5},
    {{0, 0}, 180, {4, 4}, {-4, -4}, 1e-5},
    {{0, 0}, 270, {4, 4}, {4, -4}, 1e-4},
    {{0, 0}, 360, {4, 4}, {4, 4}, 1e-4},
    {{5, 5}, 0, {4, 4}, {4, 4}, 1e-3},
    {{5, 5}, 90, {4, 4}, {6, 4}, 1e-3},
    {{5, 5}, 180, {4, 4}, {6, 6}, 1e-3},
    {{5, 5}, 270, {4, 4}, {4, 6}, 1e-3},
    {{5, 5}, 360, {4, 4}, {4, 4}, 1e-3}

};

INSTANTIATE_TEST_SUITE_P(StandardTransformations, TransformationTestWithParams,
                         testing::ValuesIn(transformationParams));
INSTANTIATE_TEST_SUITE_P(StandardTransformations,
                         TransformationTestWithParamsCyclic,
                         testing::ValuesIn(transformationParams_cyclic));
