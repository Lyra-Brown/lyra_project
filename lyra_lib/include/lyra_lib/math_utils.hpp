#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include "lyra_lib/visibility_control.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <eigen3/Eigen/Dense>

using Eigen::Matrix2d;
using Eigen::Vector2d;
using Eigen::Vector3d;

namespace Matrix
{
    inline Matrix2d rotation_matrix_2d(double theta)
    {
        Matrix2d rotation_matrix;
        rotation_matrix << std::cos(theta), -std::sin(theta),
                           std::sin(theta),  std::cos(theta);
        return rotation_matrix;
    }
}

namespace Units
{
    inline constexpr double TERA = 1.0e12;
    inline constexpr double GIGA = 1.0e9;
    inline constexpr double MEGA = 1.0e6;
    inline constexpr double KILO = 1.0e3;
    inline constexpr double HECTO = 1.0e2;
    inline constexpr double DECA = 1.0e1;
    inline constexpr double DECI = 1.0e-1;
    inline constexpr double CENTI = 1.0e-2;
    inline constexpr double MILLI = 1.0e-3;
    inline constexpr double MICRO = 1.0e-6;
    inline constexpr double NANO = 1.0e-9;
    inline constexpr double PICO = 1.0e-12;
}

// ---------- Conversion Functions ---------- //
namespace Conversion
{
LYRA_LIB_PUBLIC double convertToRadian(double degree);
LYRA_LIB_PUBLIC double convertToDegree(double radian);
LYRA_LIB_PUBLIC Vector3d convertToRobotCoordinate(Vector3d *global_coordinate_vec, double now_robot_theta, Vector3d *robot_position_vec = nullptr);
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
LYRA_LIB_PUBLIC int32_t get_minimum_int(int32_t* arr, size_t size);
LYRA_LIB_PUBLIC int32_t get_maximum_int(int32_t* arr, size_t size);
LYRA_LIB_PUBLIC int8_t get_polarity_int32(int32_t value);
LYRA_LIB_PUBLIC int8_t get_polarity_float(float value);
}
// ------------------------------------------ //

#endif // MATH_UTILS_HPP