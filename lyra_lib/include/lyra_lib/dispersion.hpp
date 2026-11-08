#ifndef DISPERSION_HPP
#define DISPERSION_HPP

#include "lyra_lib/visibility_control.h"

template<typename T>
class LYRA_LIB_PUBLIC dispersion
{
public:
    dispersion() = default;
    ~dispersion() = default;
    T update(T new_data);
    T get_dispersion() const { return dispersion_; }

private:
    T sampling_data_num = 0;
    T dispersion_ = 0;
    T data_squad_sum = 0;
    T data_sum = 0;
};

#endif // DISPERSION_HPP
