#include <Interpolator.h>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <QString>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

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

    void saveImg(QImage& output_image, Parameters params, QString path)
    {
        output_image.save(
            output_path.absoluteFilePath() + path + "BITMAPA_transformed_" +
            QString::number(params.angle) + "_st_" +
            QString::number(params.led_size) + "_led_size_" +
            QString::number(params.led_number) + "_led_number.png");
    }

    QFileInfo pixmap_path{"C:\\Users\\mplesniak\\Desktop\\1. "
                          "Mentoring_QT_project\\Spectral_Display_"
                          "GUI\\build\\bin\\UnitTests\\Pictures\\BITMAPA.png"};

    QFileInfo output_path{
        pixmap_path.absoluteFilePath() +
        "\\..\\..\\TestSinglePointTransformLibibrary\\GeneratedPicture\\"};

    QPixmap* pix_map;
    QGuiApplication* app;
    Interpolator* interpolator;
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{
    {1, 1, 240}, {2, 1, 120}, {3, 1, 80},  {5, 1, 40},  {10, 1, 24},
    {15, 1, 10}, {20, 1, 50}, {25, 1, 50}, {30, 1, 50}, {35, 1, 50}};

TEST_P(InterpolationTestWithParams, test_library)
{
    auto& params = GetParam();

    QImage output_image = interpolator->transformImage(
        params.angle, params.led_size, params.led_number);
    saveImg(output_image, params, "test_library\\");

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));