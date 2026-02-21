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

Vector3d convertToRobotCoordinate(Vector3d *global_coordinate_vec, double now_robot_theta, Vector3d *robot_position_vec) 
{
    // Create a rotation matrix based on the robot's current orientation
    Matrix2d rotation_matrix = Matrix::rotation_matrix_2d(-now_robot_theta); // Negative for inverse rotation

    // Create a vector for the global coordinate
    Vector2d global_vector(global_coordinate_vec->x(), global_coordinate_vec->y());

    // Rotate the global vector to align with the robot's orientation
    Vector2d rotated_vector = rotation_matrix * global_vector;

    // The robot's local coordinate is the rotated vector plus the robot's origin (which is now at (0, 0))
    Vector3d local_coordinate(rotated_vector.x(), rotated_vector.y(), now_robot_theta);

    if(robot_position_vec != nullptr)
    {
        robot_position_vec->x() = local_coordinate.x();
        robot_position_vec->y() = local_coordinate.y();
        robot_position_vec->z() = local_coordinate.z();
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