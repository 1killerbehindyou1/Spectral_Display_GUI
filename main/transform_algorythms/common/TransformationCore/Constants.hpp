#pragma once

namespace common
{
namespace constants
{

/** @brief Mathematical constant π. */
constexpr double pi = 3.141592653589793238462643383279502884197169399375L;
/** @brief Mathematical constant 2π. */
constexpr double two_pi = 2 * pi;
/** @brief Reciprocal value of π. */
constexpr double inv_pi = 1 / pi;

/**
 * @brief Converts angle from degrees to radians.
 * @tparam T Numeric type of the input angle.
 * @param deg Angle in degrees.
 * @return Angle in radians.
 */
template <typename T>
constexpr inline double degToRad(T deg)
{
    return deg * pi / 180.0;
}

} // namespace constants
} // namespace common
