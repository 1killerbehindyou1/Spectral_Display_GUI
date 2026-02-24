#include <CommonTestsImpl.hpp>
#include <InterpolatorSingle.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <QString>

struct Parameters
{
    int led_size;
    int angle;
    int led_number;
    QPoint m_point;
};

class InterpolationTestWithParams
    : public test_utils::SaveLoadFixture<Parameters>,
      public test_utils::InterpolatorInstanceFixture<single::InterpolatorSingle>
{
public:
    InterpolationTestWithParams(const char* inp = INPUT_IMG_PATH,
                                const char* out = OUTPUT_IMG_PATH)
        : SaveLoadFixture(inp, out)
    {
    }
};

std::vector<Parameters> param_1{
    {1, 1, 240, QPoint(0, 0)}, {2, 1, 120, QPoint(0, 0)}, {3, 1, 80, QPoint(0, 0)},  {5, 1, 40, QPoint(0, 0)},  {10, 1, 24, QPoint(0, 0)}, {15, 1, 16, QPoint(0, 0)}, {20, 1, 12, QPoint(0, 0)}, {25, 1, 10, QPoint(0, 0)}, {30, 1, 8, QPoint(0, 0)}, {35, 1, 6, QPoint(0, 0)},
     {1, 1, 240, QPoint(0, 0)},          {2, 1, 120, QPoint(0, 0)},          {3, 1, 80, QPoint(0, 0)},           {5, 1, 40, QPoint(0, 0)},           {10, 1, 24, QPoint(0, 0)},
    {15, 1, 10, QPoint(0, 0)}, {20, 1, 50, QPoint(0, 0)}, {25, 1, 50, QPoint(0, 0)}, {30, 1, 50, QPoint(0, 0)}, {35, 1, 50, QPoint(0, 0)},
     {1, 1, 240, QPoint(0, 0)},          {2, 1, 120, QPoint(0, 0)},          {3, 1, 80, QPoint(0, 0)},           {5, 1, 40, QPoint(0, 0)},           {10, 1, 24, QPoint(0, 0)},
    {15, 1, 10, QPoint(0, 0)}, {20, 1, 50, QPoint(0, 0)}, {25, 1, 50, QPoint(0, 0)}, {30, 1, 50, QPoint(0, 0)}, {35, 1, 50, QPoint(0, 0)}};

TEST_P(InterpolationTestWithParams, test_library)
{
    auto& params = GetParam();

    QImage output_image = interpolator->transformImage(
        params.angle, params.led_size, params.led_number, params.m_point, pix_map);
    saveImg(output_image, params, "test_library");
    std::cout << pixmap_path.absoluteFilePath().toStdString() << std::endl;
    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));