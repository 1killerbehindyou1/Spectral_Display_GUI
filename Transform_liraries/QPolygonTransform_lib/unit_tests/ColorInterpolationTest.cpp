#include "TestUtils.hpp"
#include <Interpolator.h>

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
struct Parameters
{
    int led_size;
    int led_number;
};

class ColorInterpolationTestWithParams
    : public testing::TestWithParam<Parameters>
{

public:
    ColorInterpolationTestWithParams()
    {
        int argc{};
        char* argv[]{};
        app = new QGuiApplication{argc, argv};
        pix_map = new QPixmap{};
        pix_map->load(pixmap_path.absoluteFilePath());
        interpolator = new Interpolator{app};
        interpolator->setPixmap(pix_map);
    }
    ~ColorInterpolationTestWithParams() { delete app; }

    void printRect(QImage& img, QRect& rect)
    {
        img.setPixelColor(rect.topLeft(), "green");
        img.setPixelColor(rect.topRight(), "red");
        img.setPixelColor(rect.bottomLeft(), "blue");
        img.setPixelColor(rect.bottomRight(), "purple");
    }
    void printRect(QImage& img, QPolygonF& poly)
    {
        QStringList colors{"green", "red", "blue", "purple"};

        std::size_t idx = 0;
        for (QPointF& p : poly)
        {
            img.setPixelColor(p.toPoint(), colors[(idx++) % colors.size()]);
        }
    }
    void printRect(QImage& img, QRectF& rect_f)
    {
        img.setPixelColor(rect_f.topLeft().toPoint(), "orange");
        img.setPixelColor(rect_f.topRight().toPoint(), "orange");
        img.setPixelColor(rect_f.bottomLeft().toPoint(), "orange");
        img.setPixelColor(rect_f.bottomRight().toPoint(), "orange");
    }

    void saveImg(QImage& output_image, Parameters params, QString path)
    {
        output_image.save(
            QString{OUTPUT_IMG_PATH} + "/" + path + "/BITMAPA_transformed_" +
            QString::number(params.led_size) + "_led_size_" +
            QString::number(params.led_number) + "_led_number.png");
    }

    QFileInfo pixmap_path{QString{INPUT_IMG_PATH}};
    QFileInfo output_path{QString{OUTPUT_IMG_PATH}};

    QPixmap* pix_map;
    QGuiApplication* app;
    QPolyLib::Interpolator* interpolator;
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{{1, 7},  {2, 7},  {3, 7},  {5, 7}, {10, 5},
                                {15, 5}, {20, 4}, {25, 4}, {35, 4}};

TEST_P(ColorInterpolationTestWithParams, color_test)
{
    using namespace QPolyLib::color;
    auto& params = GetParam();
    QRectF rect{QPointF{100, 100}, QSizeF{20, 20}};
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    QPoint curr_point{};
    QPolygon poly{};

    output_image.fill(interpolator->interpolateColor(QPolygonF{rect}));
    saveImg(output_image, params, "test_color");

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations,
                         ColorInterpolationTestWithParams,
                         testing::ValuesIn(param_1));