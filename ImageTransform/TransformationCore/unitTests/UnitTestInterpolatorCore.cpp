#include <CommonTestsImpl.hpp>
#include <InterpolatorBase.hpp>
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

std::vector<Parameters> param_1{
    {1, 30, 7},  {2, 30, 7},  {3, 30, 7},  {5, 30, 7},  {10, 30, 5},
    {15, 30, 5}, {20, 30, 4}, {25, 30, 4}, {30, 30, 4}, {35, 30, 4}};

class InterpolationTestWithParams
    : public test_utils::SaveLoadFixture<Parameters>
{
public:
    InterpolationTestWithParams(const char* inp = OUTPUT_IMG_PATH,
                                const char* out = INPUT_IMG_PATH)
        : SaveLoadFixture(inp, out)
    {
    }
};

TEST_P(InterpolationTestWithParams, test_polygon_ruler_print)
{
    auto& params = GetParam();

    std::cout << output_path.absoluteFilePath().toStdString() << std::endl;

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);

    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");
    output_image.setPixelColor(rot_centr, "black");

    QPoint curr_rect_corner = rot_centr;
    for (int i = 1; i < params.led_number; i++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + params.led_size * 2);

        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect{temp_point, QSize{params.led_size, params.led_size}};

        auto rectF = QRectF(rect);
        rectF.moveCenter(curr_rect_corner);

        for (int i = 0; i <= 360 - params.angle; i += params.angle)
        {
            common::Transform transform{rot_centr, static_cast<double>(i)};
            QPointF pp = transform(curr_rect_corner);

            output_image.setPixelColor(pp.toPoint(), "green");
            auto poly = transform(rectF);
            test_utils::printRect(output_image, poly);
        }
    }

    saveImg(output_image, params, "test_polygon_ruler_print/");

    EXPECT_EQ(true, true);
}

TEST_P(InterpolationTestWithParams, test_bounding_rect_print)
{
    auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");
    output_image.setPixelColor(rot_centr, "black");

    QPoint curr_rect_corner = rot_centr;
    for (int i = 1; i < params.led_number; i++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + params.led_size * 2);

        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect{temp_point, QSize{params.led_size, params.led_size}};

        auto rectF = QRectF(rect);
        rectF.moveCenter(curr_rect_corner);

        for (int i = 0; i <= 360 - params.angle; i += params.angle)
        {
            common::Transform transform{rot_centr, static_cast<double>(i)};
            QPointF pp = transform(curr_rect_corner);

            output_image.setPixelColor(pp.toPoint(), "green");
            auto poly = transform(rectF);

            test_utils::printRect(output_image, poly);
            QRectF rect_boundig_f = poly.boundingRect();
            test_utils::printRect(output_image, rect_boundig_f);
        }
    }

    saveImg(output_image, params, "test_bounding_rect_print/");

    EXPECT_EQ(true, true);
}
TEST_P(InterpolationTestWithParams, test_polygon_contains_point)
{
    auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");
    output_image.setPixelColor(rot_centr, "black");

    QPoint curr_rect_corner = rot_centr;
    for (int i = 1; i < params.led_number; i++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + params.led_size * 2);

        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect{temp_point, QSize{params.led_size, params.led_size}};

        auto rectF = QRectF(rect);
        rectF.moveCenter(curr_rect_corner);

        for (int i = 0; i <= 360 - params.angle; i += params.angle)
        {
            common::Transform transform{rot_centr, i};
            QPointF pp = transform(curr_rect_corner);

            output_image.setPixelColor(pp.toPoint(), "green");
            auto poly = transform(rectF);

            QRectF rect_boundig_f = poly.boundingRect();
            test_utils::printRect(output_image, rect_boundig_f);

            QPointF curr_point{};
            for (float y = 0; y < rect_boundig_f.height(); y++)
            {
                curr_point.setY(rect_boundig_f.topLeft().y() + y);

                for (int x = 0; x < rect_boundig_f.width(); x++)
                {
                    curr_point.setX(rect_boundig_f.topLeft().x() + x);

                    if (poly.containsPoint(curr_point, Qt::OddEvenFill))
                    {
                        output_image.setPixelColor(curr_point.toPoint(),
                                                   "black");
                    }
                }
            }
        }
    }

    saveImg(output_image, params, "test_polygon_contains_point/");

    EXPECT_EQ(true, true);
}

TEST_P(InterpolationTestWithParams, test_polygon_contains_point_Qt_WindingFill)
{
    auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");
    output_image.setPixelColor(rot_centr, "black");

    QPoint curr_rect_corner = rot_centr;
    for (int i = 1; i < params.led_number; i++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + params.led_size * 2);

        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect{temp_point, QSize{params.led_size, params.led_size}};

        auto rectF = QRectF(rect);
        rectF.moveCenter(curr_rect_corner);

        for (int i = 0; i <= 360 - params.angle; i += params.angle)
        {
            common::Transform transform{rot_centr, i};
            QPointF pp = transform(curr_rect_corner);

            auto poly = transform(rectF);

            QRectF rect_boundig_f = poly.boundingRect();

            QPointF curr_point{};
            for (float y = 0; y < rect_boundig_f.height(); y++)
            {
                curr_point.setY(rect_boundig_f.topLeft().y() + y);

                for (int x = 0; x < rect_boundig_f.width(); x++)
                {
                    curr_point.setX(rect_boundig_f.topLeft().x() + x);

                    if (poly.containsPoint(curr_point, Qt::WindingFill))
                    {
                        output_image.setPixelColor(curr_point.toPoint(),
                                                   "black");
                    }
                }
            }
        }
    }

    saveImg(output_image, params,
            "test_polygon_contains_point/Qt_WindingFill_");

    EXPECT_EQ(true, true);
}

TEST_P(InterpolationTestWithParams, test_polygon_contains_point_Qt_OddEvenFill)
{
    auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");
    output_image.setPixelColor(rot_centr, "black");

    QPoint curr_rect_corner = rot_centr;
    for (int i = 1; i < params.led_number; i++)
    {
        curr_rect_corner.setX(curr_rect_corner.x() + params.led_size * 2);

        auto temp_point = QPointF(curr_rect_corner);
        QRectF rect{temp_point, QSize{params.led_size, params.led_size}};

        auto rectF = QRectF(rect);
        rectF.moveCenter(curr_rect_corner);

        for (int i = 0; i <= 360 - params.angle; i += params.angle)
        {
            common::Transform transform{rot_centr, i};
            QPointF pp = transform(curr_rect_corner);

            auto poly = transform(rectF);

            QRectF rect_boundig_f = poly.boundingRect();

            QPointF curr_point{};
            for (float y = 0; y < rect_boundig_f.height(); y++)
            {
                curr_point.setY(rect_boundig_f.topLeft().y() + y);

                for (int x = 0; x < rect_boundig_f.width(); x++)
                {
                    curr_point.setX(rect_boundig_f.topLeft().x() + x);

                    if (poly.containsPoint(curr_point, Qt::OddEvenFill))
                    {
                        output_image.setPixelColor(curr_point.toPoint(),
                                                   "black");
                    }
                }
            }
        }
    }

    saveImg(output_image, params,
            "test_polygon_contains_point/Qt_OddEvenFill_");

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));