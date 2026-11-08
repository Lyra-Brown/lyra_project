#include "lyra_lib/dispersion.hpp"

template<typename T>
T dispersion<T>::update(T new_data)
{
    sampling_data_num++;
    data_squad_sum += new_data * new_data;
    data_sum += new_data;
    T average = data_sum / sampling_data_num;
    dispersion_ = data_squad_sum / sampling_data_num - average * average;
    return dispersion_;
}

template class dispersion<float>;
template class dispersion<double>;
