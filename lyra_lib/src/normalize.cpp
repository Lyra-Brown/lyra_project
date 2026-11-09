#include "lyra_lib/normalize.hpp"
#include <stdexcept>

template <typename T>
normalize_scale<T>::normalize_scale(T min, T max)
    : min_(min), max_(max) {}

template <typename T>
T normalize_scale<T>::normalize(T value)
{
    if (max_ == min_)
    {
        throw std::runtime_error("Cannot normalize when max and min are equal.");
    }
    return (value - min_) / (max_ - min_);
}

template <typename T>
T normalize_scale<T>::denormalize(T value)
{
    return value * (max_ - min_) + min_;
}

template <typename T>
void normalize_scale<T>::set_scale(T min, T max)
{
    min_ = min;
    max_ = max;
}

template <typename T>
void normalize_scale<T>::set_min(T min)
{
    min_ = min;
}

template <typename T>
void normalize_scale<T>::set_max(T max)
{
    max_ = max;
}

template class normalize_scale<float>;
template class normalize_scale<double>;
