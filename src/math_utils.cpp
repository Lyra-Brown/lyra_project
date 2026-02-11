#include "lyra_lib/math_utils.hpp"

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

int get_minimum_int(int* arr, size_t size) 
{
    int min_value = arr[0];
    for (size_t i = 1; i < size; ++i) 
    {
        if (arr[i] < min_value) 
        {
            min_value = arr[i];
        }
    }
    return min_value;
}
} // namespace MathConstants
// ------------------------------------------ //