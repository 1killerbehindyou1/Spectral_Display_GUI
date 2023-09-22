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
};

class InterpolationTestWithParams
    : public test_utils::SaveLoadFixture<Parameters>,
      public test_utils::InterpolatorInstanceFixture<single::InterpolatorSingle>
{
public:
    InterpolationTestWithParams(const char* inp = OUTPUT_IMG_PATH,
                                const char* out = INPUT_IMG_PATH)
        : SaveLoadFixture(inp, out)
    {
    }
};

std::vector<Parameters> param_1{
    {1, 1, 240}, {2, 1, 120}, {3, 1, 80},  {5, 1, 40},  {10, 1, 24},
    {15, 1, 10}, {20, 1, 50}, {25, 1, 50}, {30, 1, 50}, {35, 1, 50}};

TEST_P(InterpolationTestWithParams, test_library)
{
    auto& params = GetParam();

    QImage output_image = interpolator->transformImage(
        params.angle, params.led_size, params.led_number, pix_map);
    saveImg(output_image, params, "test_library");
    std::cout << pixmap_path.absoluteFilePath().toStdString() << std::endl;
    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));