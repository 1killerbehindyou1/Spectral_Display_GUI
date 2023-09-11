#include <CommonTests.hpp>
#include <InterpolatorSingle.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <QString>

class InterpolationTestWithParams : public test_utils::TestFixture<Params>
{
public:
    InterpolationTestWithParams()
    {
        pix_map = new QPixmap{};
        pix_map->load(pixmap_path.absoluteFilePath());
        interpolator = new single::InterpolatorSingle{};
        interpolator->setPixmap(pix_map);
    }

    void saveImg(QImage& output_image, Params params, QString path)
    {
        output_image.save(
            QString{OUTPUT_IMG_PATH} + "/" + path + "/BITMAPA_transformed_" +
            QString::number(params.angle) + "_st_" +
            QString::number(params.led_size) + "_led_size_" +
            QString::number(params.led_number) + "_led_number.png");
    }

    QFileInfo pixmap_path{QString{INPUT_IMG_PATH}};
    QFileInfo output_path{QString{OUTPUT_IMG_PATH}};

    QPixmap* pix_map;
    single::InterpolatorSingle* interpolator;
};

struct Params
{
    int led_size;
    int angle;
    int led_number;
};

std::vector<Params> param_1{{1, 1, 240}, {2, 1, 120}, {3, 1, 80},  {5, 1, 40},
                            {10, 1, 24}, {15, 1, 10}, {20, 1, 50}, {25, 1, 50},
                            {30, 1, 50}, {35, 1, 50}};

TEST_P(InterpolationTestWithParams, test_library)
{
    auto& params = GetParam();

    QImage output_image = interpolator->transformImage(
        params.angle, params.led_size, params.led_number);
    saveImg(output_image, params, "test_library");
    std::cout << pixmap_path.absoluteFilePath().toStdString() << std::endl;
    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));