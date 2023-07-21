#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

template <typename PointType>
void PrintTo(PointType&& point, std::ostream* out)
{
    *out << "Point(" << std::to_string(point.x()) << ","
         << std::to_string(point.y()) << ")";
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

template <typename T>
std::string to_string(const T& val)
{
    std::ostringstream out;
    out << val;
    return out.str();
}
