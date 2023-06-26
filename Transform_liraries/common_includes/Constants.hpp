#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{

constexpr double pi = 3.141592653589793238462643383279502884197169399375L;
constexpr double two_pi = 2 * pi;
constexpr double inv_pi = 1 / pi;
constexpr inline double degToRad(float deg) { return deg * pi / 180; }

} // namespace constants

#endif