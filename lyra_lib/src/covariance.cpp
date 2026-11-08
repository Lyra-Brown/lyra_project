#include "lyra_lib/covariance.hpp"

template<typename T>
T covariance<T>::update(T new_data_x, T new_data_y)
{
    sampling_data_num++;
    x_sum += new_data_x;
    y_sum += new_data_y;
    xy_sum += new_data_x * new_data_y;

    T x_mean = x_sum / sampling_data_num;
    T y_mean = y_sum / sampling_data_num;

    covariance_ = (xy_sum / sampling_data_num) - (x_mean * y_mean);
    return covariance_;
}

template class covariance<float>;
template class covariance<double>;
