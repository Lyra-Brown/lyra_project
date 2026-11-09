#include "lyra_lib/accelate.hpp"

template <typename T>
accelerate_limiter<T>::accelerate_limiter(T max_acceleration, T dt)
    : dt_(dt)
{
    accelerate_limiter_.set_limits(-max_acceleration, max_acceleration);
}

template <typename T>
void accelerate_limiter<T>::set_max_acceleration(T max_acceleration)
{
    accelerate_limiter_.set_max(max_acceleration);
}

template <typename T>
void accelerate_limiter<T>::set_max_deceleration(T max_deceleration)
{
    accelerate_limiter_.set_min(-max_deceleration);
}

template <typename T>
T accelerate_limiter<T>::update(T current_velocity, T target_velocity, T dt)
{
    T acceleration = (target_velocity - last_velocity_) / dt;
    output = accelerate_limiter_.set_value(acceleration);
    last_velocity_ = current_velocity;
    return output;
}

template class accelerate_limiter<float>;
template class accelerate_limiter<double>;
