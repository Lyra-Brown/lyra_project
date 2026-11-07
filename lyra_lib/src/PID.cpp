#include "lyra_lib/PID.hpp"

#include <cstdint>
#include <algorithm>
#include <stdexcept>

template <typename T>
pid_controller_base<T>::pid_controller_base(T kp_, T ki_, T kd_, T dt_)
{
    config.gains = {kp_, ki_, kd_};
    set_dt(dt_);
}

template <typename T>
pid_controller_base<T>::pid_controller_base(T kp_, T ki_, T kd_)
{
    config.gains = {kp_, ki_, kd_};
}

template <typename T>
void pid_controller_base<T>::set_gains(T kp_, T ki_, T kd_)
{
    config.gains = {kp_, ki_, kd_};
}

template <typename T>
void pid_controller_base<T>::set_dt(T dt_)
{
    if(dt_ <= 0)
    {
        throw std::invalid_argument("dt must be greater than 0");
    }
    config.dt = dt_;
}

template <typename T>
void pid_controller_base<T>::set_limits(T min_, T max_)
{
    output_limiter.set_limits(min_, max_);
}

template <typename T>
void pid_controller_base<T>::limits_enabled(bool enabled)
{
    output_limiter.enable_limits(enabled);
}

template <typename T>
void pid_controller_base<T>::toggle_limits()
{
    output_limiter.toggle_limits();
}

template <typename T>
T pid_controller_base<T>::update(T value, T target)
{
    input(value, target);
    return output_value();
}

template <typename T>
void pos_pid_controller<T>::refresh()
{
    this->error[0] = 0;
    this->error[1] = 0;
    this->error[2] = 0;
    this->output = 0;
    ie = 0;
}

template <typename T>
void pos_pid_controller<T>::input(T value, T target)
{
    this->error[0] = target - value;
    T de = (this->error[0] - this->error[1]) / this->config.dt;
    ie += (this->error[0] + this->error[1]) * this->config.dt / static_cast<T>(2);
    ie = integral_limiter.set_value(ie);
    this->output = this->config.gains.kp * this->error[0] + this->config.gains.ki * ie + this->config.gains.kd * de;
    this->output = this->output_limiter.set_value(this->output);
    this->error[1] = this->error[0];
}

template <typename T>
void pos_pid_controller<T>::set_integral_limits(T min_, T max_)
{
    integral_limiter.set_limits(min_, max_);
}

template <typename T>
void pos_pid_controller<T>::integral_limits_enabled(bool enabled)
{
    integral_limiter.enable_limits(enabled);
}

template <typename T>
void pos_pid_controller<T>::toggle_integral_limits()
{
    integral_limiter.toggle_limits();
}

template <typename T>
void vel_pid_controller<T>::refresh()
{
    this->error[0] = 0;
    this->error[1] = 0;
    this->error[2] = 0;
    this->output = 0;
}

template <typename T>
void vel_pid_controller<T>::input(T value, T target)
{
    this->error[2] = this->error[1];
    this->error[1] = this->error[0];
    this->error[0] = target - value;
    this->output += this->config.gains.kp * (this->error[0] - this->error[1]) + this->config.gains.ki * this->error[0] + this->config.gains.kd * (this->error[0] - 2 * this->error[1] + this->error[2]) / this->config.dt;
    this->output = this->output_limiter.set_value(this->output);
}

template class pid_controller_base<float>;
template class pid_controller_base<double>;
template class pos_pid_controller<float>;
template class pos_pid_controller<double>;
template class vel_pid_controller<float>;
template class vel_pid_controller<double>;
