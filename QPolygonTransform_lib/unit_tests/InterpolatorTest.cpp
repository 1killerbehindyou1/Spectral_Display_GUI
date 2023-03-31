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
    // int led_number;
    int led_size;
    int angle;
    QPoint offset;
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

    QFileInfo output_path{"C:\\Users\\mplesniak\\Pictures\\results\\"};
    QFileInfo pixmap_path{"C:\\Users\\mplesniak\\Pictures\\BITMAPA.png"};
    QPixmap* pix_map;
    QGuiApplication* app;
    Interpolator* interpolator;
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{
    {1, 30, {0, 50}},   {2, 30, {0, 50}},   {3, 30, {0, 50}},
    {5, 30, {0, 50}},   {10, 30, {0, 50}},  {15, 30, {0, 50}},
    {20, 30, {0, 50}},  {25, 30, {0, 50}},  {1, 30, {0, 100}},
    {2, 30, {0, 100}},  {3, 30, {0, 100}},  {5, 30, {0, 100}},
    {10, 30, {0, 100}}, {15, 30, {0, 100}}, {20, 30, {0, 100}},
    {25, 30, {0, 100}}};

TEST_P(InterpolationTestWithParams, initial_test)
{
    const auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");

    QRect rect{rot_centr, QSize{params.led_size, params.led_size}};
    rect.moveTo(rot_centr + params.offset);

    Transform transform{rot_centr, params.angle};
    output_image.setPixelColor(rot_centr, "black");

    for (int i = 0; i <= 360 - params.angle; i += params.angle)
    {
        output_image.setPixelColor(rect.topLeft(), "green");
        output_image.setPixelColor(rect.topRight(), "red");
        output_image.setPixelColor(rect.bottomLeft(), "blue");
        output_image.setPixelColor(rect.bottomRight(), "purple");
        rect = transform(rect);
    }

    output_image.save(output_path.absoluteFilePath() + "BITMAPA_transformed_" +
                      QString::number(params.angle) + "_st_" +
                      QString::number(params.led_size) + "_led_size_" +
                      QString::number(params.offset.y()) + "_offset_" + ".png");

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));