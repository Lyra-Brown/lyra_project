#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cmath>

double  gaussian_pdf(double x, double mean, double stddev) 
{
    const double inv_sqrt_2pi = 0.3989422804014327;
    double a = (x - mean) / stddev;
    return (inv_sqrt_2pi / stddev) * std::exp(-0.5 * a * a);
}

#endif // FUNCTION_HPP
