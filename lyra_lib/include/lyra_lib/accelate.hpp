#ifndef ACCELERATE_HPP
#define ACCELERATE_HPP

#include "lyra_lib/visibility_control.h"
#include <cstdint>
#include "lyra_lib/limiter.hpp"

template <typename T>
class LYRA_LIB_PUBLIC accelerate_limiter
{
public:
    accelerate_limiter() = default;
    accelerate_limiter(T max_acceleration, T dt = 1e-3);
    void set_max_acceleration(T max_acceleration);
    void set_max_deceleration(T max_deceleration);
    T update(T current_velocity, T target_velocity, T dt);
    T output_value() const { return output; }

private:
    limiter<T> accelerate_limiter_;
    T output = 0;
    T last_velocity_ = 0;
    T dt_ = 1e-3;
};

#endif
