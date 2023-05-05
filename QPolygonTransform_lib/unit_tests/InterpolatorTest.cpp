#include <Interpolator.h>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <QString>
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
        interpolator = new Interpolator{app};
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

    void saveImg(QImage& output_image, Parameters params)
    {
        output_image.save(
            output_path.absoluteFilePath() + "BITMAPA_transformed_" +
            QString::number(params.angle) + "_st_" +
            QString::number(params.led_size) + "_led_size_" +
            QString::number(params.led_number) + "_led_number.png");
    }

    QFileInfo output_path{"C:\\Users\\mplesniak\\Desktop\\1. "
                          "Mentoring_QT_project\\Spectral_Display_"
                          "GUI\\build\\bin\\UnitTests\\GeneratedPicture\\"};
    QFileInfo pixmap_path{"C:\\Users\\mplesniak\\Desktop\\1. "
                          "Mentoring_QT_project\\Spectral_Display_"
                          "GUI\\build\\bin\\UnitTests\\Pictures\\BITMAPA.png"};
    QPixmap* pix_map;
    QGuiApplication* app;
    Interpolator* interpolator;
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{
    {2, 30, 7},  {3, 30, 7},  {5, 30, 7},  {10, 30, 7}, {15, 30, 7},
    {20, 30, 7}, {25, 30, 7}, {1, 30, 5},  {2, 30, 5},  {3, 10, 5},
    {5, 30, 5},  {10, 30, 5}, {15, 30, 5}, {20, 30, 5}, {25, 30, 5}};

TEST_P(InterpolationTestWithParams, polygon_ruler_print)
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
            Transform transform{rot_centr, i};
            QPointF pp = transform(curr_rect_corner);

            output_image.setPixelColor(pp.toPoint(), "green");
            auto poly = transform(QPolygonF(rectF));
            printRect(output_image, poly);
        }
    }

    saveImg(output_image, params);

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));