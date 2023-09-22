#pragma once
#include <InterpolatorBase.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>

namespace test_utils
{

template <typename Parameters>
class SaveLoadFixture : public testing::TestWithParam<Parameters>
{
public:
    SaveLoadFixture(const char* input, const char* output);
    ~SaveLoadFixture(){};

    void saveImg(QImage& output_image, Parameters params, QString path);

    QFileInfo pixmap_path;
    QFileInfo output_path;
    QPixmap* pix_map;
};

template <typename Interpolator>
class InterpolatorInstanceFixture
{
public:
    InterpolatorInstanceFixture();
    ~InterpolatorInstanceFixture(){};

    std::unique_ptr<Interpolator> interpolator;
};

template <typename T>
std::string to_string(const T& val);

template <typename PointType,
          typename = decltype(std::declval<PointType>().x() +
                              std::declval<PointType>().y())>
std::ostream& operator<<(std::ostream& out,
                         PointType&& point); // universal reference

template <typename PointType>
void PrintTo(PointType&& point, std::ostream* out);

}; // namespace test_utils