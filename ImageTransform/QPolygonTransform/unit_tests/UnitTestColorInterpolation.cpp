#include "CommonTestsImpl.hpp"
#include <ColorCalc.hpp>
#include <InterpolatorQPoly.hpp>

struct Parameters
{
    int led_size;
    int led_number;
};

class ColorInterpolationTestWithParams
    : public test_utils::SaveLoadFixture<Parameters>,
      public test_utils::InterpolatorInstanceFixture<poly::InterpolatorQPoly>
{

public:
    ColorInterpolationTestWithParams(const char* inp = INPUT_IMG_PATH,
                                     const char* out = OUTPUT_IMG_PATH)
        : SaveLoadFixture(inp, out)
    {
    }
};

std::vector<Parameters> param_1{{1, 7},  {2, 7},  {3, 7},  {5, 7}, {10, 5},
                                {15, 5}, {20, 4}, {25, 4}, {35, 4}};

TEST_P(ColorInterpolationTestWithParams, color_test)
{
    auto& params = GetParam();

    QRectF rect{QPointF{100, 100}, QSizeF{20, 20}};
    QImage output_image{pix_map->size(), QImage::Format_RGB32};

    output_image.fill(interpolator->interpolateColor(QPolygonF{rect}, pix_map));
    saveImg(output_image, params, "test_color");

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations,
                         ColorInterpolationTestWithParams,
                         testing::ValuesIn(param_1));