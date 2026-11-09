#ifndef NORMALIZE_HPP
#define NORMALIZE_HPP

#include "lyra_lib/visibility_control.h"

template <typename T = double>
class LYRA_LIB_PUBLIC normalize_scale
{
public:
    normalize_scale() = default;
    normalize_scale(T min, T max);
    ~normalize_scale() = default;

    T normalize(T value);
    T denormalize(T value);
    void set_scale(T min, T max);
    void set_min(T min);
    void set_max(T max);

private:
    T min_ = 0;
    T max_ = 1;
};

#endif // NORMALIZE_HPP
