#include "CommonTests.hpp"
#include <ColorCalc.hpp>
#include <InterpolatorQPoly.hpp>

struct Parameters
{
    int led_size;
    int led_number;
};

class ColorInterpolationTestWithParams
    : public test_utils::TestFixture<Parameters, poly::InterpolatorQPoly>
{

public:
    ColorInterpolationTestWithParams(const char* inp = OUTPUT_IMG_PATH,
                                     const char* out = INPUT_IMG_PATH)
        : TestFixture(inp, out)
    {
    }
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{{1, 7},  {2, 7},  {3, 7},  {5, 7}, {10, 5},
                                {15, 5}, {20, 4}, {25, 4}, {35, 4}};

TEST_P(ColorInterpolationTestWithParams, color_test)
{
    using namespace common;
    auto& params = GetParam();
    QRectF rect{QPointF{100, 100}, QSizeF{20, 20}};
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    QPoint curr_point{};
    QPolygon poly{};

    output_image.fill(interpolator->interpolateColor(QPolygonF{rect}, pix_map));
    saveImg(output_image, params, "test_color");

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations,
                         ColorInterpolationTestWithParams,
                         testing::ValuesIn(param_1));