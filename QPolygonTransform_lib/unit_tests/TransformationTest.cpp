#include <QDebug>
#include <QString>
#include <Transformation.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

void PrintTo(const QPointF& point, std::ostream* out) {
    *out << "QPointF(" << std::to_string(point.x()) << "," << std::to_string(point.y()) << ")";
}

void PrintTo(const QPoint& point, std::ostream* out) {
    *out << "QPoint(" << std::to_string(point.x()) << "," << std::to_string(point.y()) << ")";
}

std::ostream& operator<<(std::ostream& out, const QPointF& point) {
    return out << "QPointF(" << std::to_string(point.x()) << "," << std::to_string(point.y()) << ")";
}

std::ostream& operator<<(std::ostream& out, const QPoint& point) {
    return out << "QPointF(" << std::to_string(point.x()) << "," << std::to_string(point.y()) << ")";
}

template<typename T>
std::string to_string(const T& val) {
    std::ostringstream out;
    out << val;
    return out.str();
}

MATCHER_P2(EQUAL_TO_POINT, expectedPoint, delta, QString("%1 equeal to %2 with delta %3").arg(negation ? "isn't" : "is").arg(to_string(expectedPoint).c_str()).arg(delta).toStdString()) {
    auto diff = arg - expectedPoint;

    return abs(diff.x()) < delta || abs(diff.y()) < delta;
}

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

struct TransformationParams {
    QPoint rotationCenter;
    float rotationAngle;
    QPointF inputPoint;
    QPointF expectedResult;

    friend void PrintTo(const TransformationParams& params, std::ostream* out) {
        *out << "rotP:";
        PrintTo(params.rotationCenter, out);
        *out << " rotAng:" << params.rotationAngle << "st.";
        *out << " inP:";
        PrintTo(params.inputPoint, out);
        *out << " res:";
        PrintTo(params.expectedResult, out);
    }
};

class TransformationTestWithParams :
    public testing::TestWithParam<TransformationParams> {
  // You can implement all the usual fixture class members here.
  // To access the test parameter, call GetParam() from class
  // TestWithParam<T>.
};

TEST_P(TransformationTestWithParams, properlyTranformPoint) {
    const auto& params = GetParam();

    Transform transform{params.rotationCenter, params.rotationAngle};

    auto result = transform(params.inputPoint);
    EXPECT_NEAR(result.x(), params.expectedResult.x(), 1e-5);
    EXPECT_NEAR(result.y(), params.expectedResult.y(), 1e-5);
}

TEST_P(TransformationTestWithParams, properlyTranformPoint_v2) {
    const auto& params = GetParam();

    Transform transform{params.rotationCenter, params.rotationAngle};

    EXPECT_THAT(transform(params.inputPoint), EQUAL_TO_POINT(params.expectedResult, 1e-5));
}

std::vector<TransformationParams> transformationParams {
    {{0,0}, 0, {1,0}, {1,0}},
    {{0,0}, 90, {1,0}, {0,1}},
    {{0,0}, 180, {1,0}, {-1,0}},
    {{0,0}, 270, {1,0}, {0,-1}},
    {{0,0}, -180, {1,0}, {-1,0}},
    {{0,0}, 187, {0,0}, {0,0}},
    {{0,0}, 30, {1,0}, {std::sqrt(3)*0.5,0.5}},
    {{0,0}, 90+30, {1,0}, {-0.5, std::sqrt(3)*0.5}},
    {{1,1}, 270, {1,0}, {2,1}},
    {{1,1}, 90, {1,0}, {0,1}},
    {{1,1}, 180, {1,0}, {1,2}},
    {{1,1}, 0, {1,0}, {1,0}},
};

INSTANTIATE_TEST_SUITE_P(StandardTransformations,
                         TransformationTestWithParams,
                         testing::ValuesIn(transformationParams));

