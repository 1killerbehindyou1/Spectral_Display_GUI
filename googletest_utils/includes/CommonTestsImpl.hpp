#pragma once
#include <CommonTests.hpp>

namespace test_utils
{

template <typename Parameters>
SaveLoadFixture<Parameters>::SaveLoadFixture(const char* input,
                                             const char* output)
    : pixmap_path{QFileInfo{QString{input}}}, output_path{
                                                  QFileInfo{QString{output}}}
{
    pix_map->load(pixmap_path.absoluteFilePath());
}

template <typename Parameters>
void SaveLoadFixture<Parameters>::saveImg(QImage& output_image,
                                          Parameters params, QString path)
{
    output_image.save(output_path.absoluteFilePath() + "/" + path +
                      "/BITMAPA_transformed_" +
                      QString::number(params.led_size) + "_led_size_" +
                      QString::number(params.led_number) + "_led_number.png");
}

template <typename Interpolator>
InterpolatorInstanceFixture<Interpolator>::InterpolatorInstanceFixture()
    : interpolator{std::make_unique<Interpolator>()}
{
}

template <typename T>
std::string to_string(const T& val)
{
    std::ostringstream out;
    out << val;
    return out.str();
}

template <typename PointType,
          typename = decltype(std::declval<PointType>().x() +
                              std::declval<PointType>().y())>
std::ostream& operator<<(std::ostream& out,
                         PointType&& point) // universal reference
{
    return out << "Point(" << std::to_string(point.x()) << ","
               << std::to_string(point.y()) << ")";
}

template <typename PointType>
void PrintTo(PointType&& point, std::ostream* out)
{
    *out << "Point(" << std::to_string(point.x()) << ","
         << std::to_string(point.y()) << ")";
}

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
}; // namespace test_utils

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