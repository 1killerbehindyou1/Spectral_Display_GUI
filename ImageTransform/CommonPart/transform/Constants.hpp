#pragma once

namespace common
{
namespace constants
{

constexpr double pi = 3.141592653589793238462643383279502884197169399375L;
constexpr double two_pi = 2 * pi;
constexpr double inv_pi = 1 / pi;

template <typename T>
constexpr inline double degToRad(T deg)
{
    return deg * pi / 180;
}

} // namespace constants
} // namespace common
