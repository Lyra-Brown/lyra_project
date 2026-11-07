#ifndef FILTER_HPP
#define FILTER_HPP

#include "lyra_lib/visibility_control.h"
#include <cstdint>

template <typename T>
class LYRA_LIB_PUBLIC low_pass_filter
{
public:
    low_pass_filter() = default;
    low_pass_filter(T alpha_);
    void set_alpha(T alpha_);
    T update(T value);

private:
    T alpha_;
    T last_value_ = 0;
};

#endif // FILTER_HPP
