#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include "lyra_lib/visibility_control.h"
#include <cmath>

constexpr double TERA = 1.0e12;
constexpr double GIGA = 1.0e9;
constexpr double MEGA = 1.0e6;
constexpr double KILO = 1.0e3;
constexpr double HECTO = 1.0e2;
constexpr double DECA = 1.0e1;
constexpr double DECI = 1.0e-1;
constexpr double CENTI = 1.0e-2;
constexpr double MILLI = 1.0e-3;
constexpr double MICRO = 1.0e-6;
constexpr double NANO = 1.0e-9;
constexpr double PICO = 1.0e-12;


// ---------- Conversion Functions ---------- //
namespace Conversion
{
LYRA_LIB_PUBLIC double convertToRadian(double degree);
LYRA_LIB_PUBLIC double convertToDegree(double radian);
}
// ------------------------------------------ //


// ---------- Normalization Functions ---------- //
namespace Normalization
{
LYRA_LIB_PUBLIC double normalizeRadian(double radian);
LYRA_LIB_PUBLIC double normalizeDegree(double degree);
}
// --------------------------------------------- //


// ---------- Mathematical Constants ---------- //
namespace MathConstants
{
LYRA_LIB_PUBLIC float get_minimum_float(float* arr, size_t size);
LYRA_LIB_PUBLIC double get_minimum_double(double* arr, size_t size);
LYRA_LIB_PUBLIC int get_minimum_int(int* arr, size_t size);
}
// ------------------------------------------ //

#endif // MATH_UTILS_HPP