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
    int led_number;
    int led_size;
    int angle;
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

    QFileInfo output_path{
        "C:\\Users\\mplesniak\\Pictures\\BITMAPA_transformed.png"};
    QFileInfo pixmap_path{"C:\\Users\\mplesniak\\Pictures\\BITMAPA.png"};
    QPixmap* pix_map;
    QGuiApplication* app;
    Interpolator* interpolator;
};

///////////////////////////////////////////////////////////////
std::vector<Parameters> param_1{{
    100,
    10,
    1,
}};

TEST_P(InterpolationTestWithParams, initial_test)
{
    const auto& params = GetParam();

    QPoint rot_centr(pix_map->width() / 2, pix_map->height() / 2);
    QImage output_image{pix_map->size(), QImage::Format_RGB32};
    output_image.fill("white");

    QPoint offset{40, 0};

    QRect rect{rot_centr, QSize{params.led_size, params.led_size}};
    rect.moveTo(rot_centr + offset);
    qDebug() << rect;
    output_image.setPixelColor(rot_centr, "black");
    output_image.setPixelColor(rect.topLeft(), "red");
    output_image.setPixelColor(rect.topRight(), "red");
    output_image.setPixelColor(rect.bottomLeft(), "red");
    output_image.setPixelColor(rect.bottomRight(), "red");
    // QColor result = interpolator->interpolateColor(transform, rect);

    Transform transform{rot_centr, 90};

    output_image.save(output_path.absoluteFilePath());

    EXPECT_EQ(true, true);
}

INSTANTIATE_TEST_SUITE_P(StandardTransformations, InterpolationTestWithParams,
                         testing::ValuesIn(param_1));