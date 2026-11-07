#include "lyra_lib/filter.hpp"

template <typename T>
low_pass_filter<T>::low_pass_filter(T alpha_)
    : alpha_(alpha_)
{
}

template <typename T>
void low_pass_filter<T>::set_alpha(T alpha_)
{
    alpha_ = alpha_;
}

template <typename T>
T low_pass_filter<T>::update(T value)
{
    last_value_ = alpha_ * value + (1 - alpha_) * last_value_;
    return last_value_;
}

template class low_pass_filter<float>;
template class low_pass_filter<double>;
