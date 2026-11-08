#ifndef CONVARIANCE_HPP
#define CONVARIANCE_HPP

#include "lyra_lib/visibility_control.h"

template<typename T>
class LYRA_LIB_PUBLIC covariance
{
public:
    covariance() = default;
    ~covariance() = default;
    T update(T new_data_x, T new_data_y);
    T get_covariance() const { return covariance_; }

private:
    T sampling_data_num = 0;
    T x_sum = 0;
    T y_sum = 0;
    T xy_sum = 0;
    T covariance_ = 0;
};

#endif // CONVARIANCE_HPP
