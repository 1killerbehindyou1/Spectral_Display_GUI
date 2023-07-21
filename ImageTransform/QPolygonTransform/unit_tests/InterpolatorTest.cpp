#include "CommonTests.hpp"
#include <InterpolatorQPoly.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <QString>

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

struct Parameters
{
    int led_size;
    int angle;
    int led_number;
};

class InterpolationTestWithParams : public testing::TestWithParam<Parameters>
{
public:
    InterpolationTestWithParams()
    {
        int argc{};
        char* argv[]{};
        app = new QGuiApplication{argc, argv};
        pix_map = new QPixmap{};
        pix_map->load(pixmap_path.absoluteFilePath());
        interpolator = new QPolyLib::Interpolator{app};
        interpolator->setPixmap(pix_map);
    }
    ~InterpolationTestWithParams() { delete app; }

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
            QString{OUTPUT_IMG_PATH} + "/" + path + "BITMAPA_transformed_" +
            QString::number(params.angle) + "_st_" +
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
std::vector<Parameters> param_1{
    {1, 30, 7},  {2, 30, 7},  {3, 30, 7},  {5, 30, 7},  {10, 30, 5},
    {15, 30, 5}, {20, 30, 4}, {25, 30, 4}, {30, 30, 4}, {35, 30, 4}};

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
            common::Transform transform{rot_centr, i};
            QPointF pp = transform(curr_rect_corner);

            output_image.setPixelColor(pp.toPoint(), "green");
            auto poly = transform(QPolygonF(rectF));
            printRect(output_image, poly);
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
            common::Transform transform{rot_centr, i};
            QPointF pp = transform(curr_rect_corner);

            output_image.setPixelColor(pp.toPoint(), "green");
            auto poly = transform(QPolygonF(rectF));

            printRect(output_image, poly);
            QRectF rect_boundig_f = poly.boundingRect();
            printRect(output_image, rect_boundig_f);
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
            auto poly = transform(QPolygonF(rectF));

            QRectF rect_boundig_f = poly.boundingRect();
            printRect(output_image, rect_boundig_f);

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

            auto poly = transform(QPolygonF(rectF));

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

            auto poly = transform(QPolygonF(rectF));

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