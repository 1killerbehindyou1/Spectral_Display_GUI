#include <QDebug>
#include <QString>
#include <Transformation.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

void PrintTo(const QPointF& point, std::ostream* out)
{
    *out << "QPointF(" << std::to_string(point.x()) << ","
         << std::to_string(point.y()) << ")";
}

void PrintTo(const QPoint& point, std::ostream* out)
{
    *out << "QPoint(" << std::to_string(point.x()) << ","
         << std::to_string(point.y()) << ")";
}

std::ostream& operator<<(std::ostream& out, const QPointF& point)
{
    return out << "QPointF(" << std::to_string(point.x()) << ","
               << std::to_string(point.y()) << ")";
}

std::ostream& operator<<(std::ostream& out, const QPoint& point)
{
    return out << "QPoint(" << std::to_string(point.x()) << ","
               << std::to_string(point.y()) << ")";
}

//////////////////////////////////////////////////////

template <typename T>
std::string to_string(const T& val)
{
    std::ostringstream out;
    out << val;
    return out.str();
}

//////////////////////////////////////////////////////

MATCHER_P2(EQUAL_TO_POINT, expectedPoint, delta,
           QString("%1 equeal to %2 with delta %3")
               .arg(negation ? "isn't" : "is")
               .arg(to_string(expectedPoint).c_str())
               .arg(delta)
               .toStdString())
{
    auto diff = arg - expectedPoint;

    return abs(diff.x()) < delta || abs(diff.y()) < delta;
}

//////////////////////////////////////////////////////

struct TransformationParams
{
    QPoint rotationCenter;
    float rotationAngle;
    QPointF inputPoint;
    QPointF expectedResult;
    double precision = 1e-5;

    friend void PrintTo(const TransformationParams& params, std::ostream* out)
    {
        *out << "rotP:";
        PrintTo(params.rotationCenter, out);
        *out << " rotAng:" << params.rotationAngle << "st.";
        *out << " inP:";
        PrintTo(params.inputPoint, out);
        *out << " res:";
        PrintTo(params.expectedResult, out);
    }
};

class TransformationTestWithParams
    : public testing::TestWithParam<TransformationParams>
{
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class
    // TestWithParam<T>.
};
class TransformationTestWithParamsCyclic
    : public testing::TestWithParam<TransformationParams>
{
    // You can implement all the usual fixture class members here.
    // To access the test parameter, call GetParam() from class
    // TestWithParam<T>.
};
//////////////////////////////////////////////////////

TEST_P(TransformationTestWithParams, properlyTransformPoint)
{

    const auto& params = GetParam();

    Transform transform{params.rotationCenter, params.rotationAngle};
    QPointF point_out = transform(params.inputPoint);

    EXPECT_NEAR(params.expectedResult.x(), point_out.x(), params.precision);
    EXPECT_NEAR(params.expectedResult.y(), point_out.y(), params.precision);
}

TEST_P(TransformationTestWithParamsCyclic, verifyCyclicTransforamtion)
{
    const auto& params = GetParam();

    Transform transform{params.rotationCenter, params.rotationAngle};
    QPointF point_in{params.inputPoint};

    for (int i = 0; i <= 360 - params.rotationAngle; i += params.rotationAngle)
    {
        point_in = transform(point_in);
    }
    EXPECT_NEAR(params.expectedResult.x(), point_in.x(), params.precision);
    EXPECT_NEAR(params.expectedResult.y(), point_in.y(), params.precision);
}
/*TEST_P(TransformationTestWithParams, properlyTranformPoint_v2)
{
    const auto& params = GetParam();

    Transform transform{params.rotationCenter, params.rotationAngle};

    EXPECT_THAT(transform(params.inputPoint),
                EQUAL_TO_POINT(params.expectedResult, 1e-5));
}*/
std::vector<TransformationParams> transformationParams_cyclic{
    {{0, 0}, 90, {1, 1}, {1, 1}, 1e-3},
    {{0, 0}, 30, {1, 1}, {1, 1}, 1e-2},
    {{0, 0}, 10, {1, 1}, {1, 1}, 1e-2},
    {{0, 0}, 1, {1, 1}, {1, 1}, 0.1},
    //
    {{0, 0}, 90, {5, 5}, {5, 5}, 0.1},
    {{0, 0}, 30, {5, 5}, {5, 5}, 0.1},
    {{0, 0}, 10, {5, 5}, {5, 5}, 0.1},
    {{0, 0}, 1, {5, 5}, {5, 5}, 0.2},
    {{10, 10}, 90, {5, 5}, {5, 5}, 0.1},
    {{10, 10}, 30, {5, 5}, {5, 5}, 0.1},
    {{10, 10}, 10, {5, 5}, {5, 5}, 0.1},
    {{10, 10}, 1, {5, 5}, {5, 5}, 0.2},
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
