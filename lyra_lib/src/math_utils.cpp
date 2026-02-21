#include "lyra_lib/math_utils.hpp"
#include <cstdint>

// ---------- Conversion Functions ---------- //
namespace Conversion
{
double convertToRadian(double degree) 
{
    return degree * M_PI / 180.0;
}

double convertToDegree(double radian) 
{
    return radian * 180.0 / M_PI;
}

Coordinate2d convertToRobotCoordinate2d(const Coordinate2d *global_coordinate_vel, double robot_theta, Coordinate2d *out_robot_coordinate_vel) 
{
    // Create a rotation matrix based on the robot's current orientation
    Eigen::Rotation2Dd rotation(- robot_theta);

    // Create a vector for the global coordinate
    Vector2d global_vector = global_coordinate_vel->position;

    // Rotate the global vector to align with the robot's orientation
    Vector2d rotated_vector = rotation * global_vector;

    // The robot's local coordinate is the rotated vector plus the robot's origin (which is now at (0, 0))
    Coordinate2d local_coordinate;
    local_coordinate.position = rotated_vector;
    local_coordinate.angle = global_coordinate_vel->angle;

    if(out_robot_coordinate_vel != nullptr)
    {
        *out_robot_coordinate_vel = local_coordinate;
    }

    return local_coordinate;
}
} // namespace Conversion
// ------------------------------------------ //


// ---------- Normalization Functions ---------- //
namespace Normalization
{
double normalizeRadian(double radian) 
{
    while (radian > M_PI) radian -= 2 * M_PI;
    while (radian <= -M_PI) radian += 2 * M_PI;
    return radian;
}

double normalizeDegree(double degree) 
{
    while (degree > 180.0) degree -= 360.0;
    while (degree <= -180.0) degree += 360.0;
    return degree;
}
} // namespace Normalization
// --------------------------------------------- //


// ---------- Mathematical Constants ---------- //
namespace MathConstants
{
float get_minimum_float(float* arr, size_t size) 
{
    float min_value = arr[0];
    for (size_t i = 1; i < size; ++i) 
    {
        if (arr[i] < min_value) 
        {
            min_value = arr[i];
        }
    }
    return min_value;
}

double get_minimum_double(double* arr, size_t size) 
{
    double min_value = arr[0];
    for (size_t i = 1; i < size; ++i) 
    {
        if (arr[i] < min_value) 
        {
            min_value = arr[i];
        }
    }
    return min_value;
}

int32_t get_minimum_int(int32_t* arr, size_t size) 
{
    int32_t min_value = arr[0];
    for (size_t i = 1; i < size; ++i) 
    {
        if (arr[i] < min_value) 
        {
            min_value = arr[i];
        }
    }
    return min_value;
}

int32_t get_maximum_int(int32_t* arr, size_t size) 
{
    int32_t max_value = arr[0];
    for (size_t i = 1; i < size; ++i) 
    {
        if (arr[i] > max_value) 
        {
            max_value = arr[i];
        }
    }
    return max_value;
}

int8_t get_polarity_int32(int32_t value) 
{
    if (value > 0) return 1;
    else if (value < 0) return -1;
    else return 0;
}

int8_t get_polarity_float(float value) 
{
    if (value > 0.0f) return 1;
    else if (value < 0.0f) return -1;
    else return 0;
}
} // namespace MathConstants
// ------------------------------------------ //