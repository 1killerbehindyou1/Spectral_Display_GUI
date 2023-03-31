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
    QPoint offset;
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

    void saveImg(QImage& output_image, Parameters params)
    {
        output_image.save(
            output_path.absoluteFilePath() + "BITMAPA_transformed_" +
            QString::number(params.angle) + "_st_" +
            QString::number(params.led_size) + "_led_size_" +
            QString::number(params.offset.y()) + "_offset_" + ".png");
    }

    QFileInfo output_path{"C:\\Users\\mplesniak\\Pictures\\results\\"};
    QFileInfo pixmap_path{"C:\\Users\\mplesniak\\Pictures\\BITMAPA.png"};
    QPixmap* pix_map;
    QGuiApplication* app;
    Interpolator* interpolator;
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{
    {1, 30, {0, 50}, 10},   {2, 30, {0, 50}, 10},   {3, 30, {0, 50}, 10},
    {5, 30, {0, 50}, 10},   {10, 30, {0, 50}, 10},  {15, 30, {0, 50}, 10},
    {20, 30, {0, 50}, 10},  {25, 30, {0, 50}, 10},  {1, 30, {0, 100}, 10},
    {2, 30, {0, 100}, 10},  {3, 10, {0, 100}, 10},  {5, 10, {0, 100}, 10},
    {10, 10, {0, 100}, 10}, {15, 10, {0, 100}, 10}, {20, 30, {0, 100}, 10},
    {25, 30, {0, 100}, 10}};

TEST_P(InterpolationTestWithParams, initial_test)
{
    const auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");

    QPointF p{};
    p += rot_centr + params.offset;
    // rect.moveTo(rot_centr + params.offset);

    output_image.setPixelColor(rot_centr, "black");
    QRect rect{rot_centr, QSize{params.led_size, params.led_size}};

    for (int i = 0; i <= 360 - params.angle; i += params.angle)
    {
        Transform transform{rot_centr, params.angle};

        for (int s = 0; s <= params.led_number; s++)
        {
            p = transform(p);
            QPointF pp = p;
            pp.setX(pp.x() + params.led_size);
            pp.setY(pp.y() + params.led_size);
            output_image.setPixelColor(pp.toPoint(), "green");
            rect.moveCenter(pp.toPoint());
            printRect(output_image, rect);
        }
    }

    saveImg(output_image, params);

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));