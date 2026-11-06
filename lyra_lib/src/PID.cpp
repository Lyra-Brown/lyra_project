#include "lyra_lib/PID.hpp"

#include <cstdint>
#include <algorithm>

template <typename T>
T IPIDController<T>::update(T value, T target)
{
    Input(value, target);
    return Output();
}

template <typename T>
void Pos_PIDController<T>::refresh()
{
    this->error[0] = 0;
    this->error[1] = 0;
    this->error[2] = 0;
    this->output = 0;
    ie = 0;
}

template <typename T>
void Pos_PIDController<T>::Input(T value, T target)
{
    this->error[0] = target - value;
    T de = (this->error[0] - this->error[1]) / this->config.dt;
    ie += (this->error[0] + this->error[1]) * this->config.dt / static_cast<T>(2);
    if(ie_limits.enabled) ie = std::clamp(ie, ie_limits.min, ie_limits.max);
    this->output = this->config.gains.kp * this->error[0] + this->config.gains.ki * ie + this->config.gains.kd * de;
    if(this->config.limits.enabled) this->output = std::clamp(this->output, this->config.limits.min, this->config.limits.max);
    this->error[1] = this->error[0];
}

template <typename T>
void Vel_PIDController<T>::refresh()
{
    this->error[0] = 0;
    this->error[1] = 0;
    this->error[2] = 0;
    this->output = 0;
}

template <typename T>
void Vel_PIDController<T>::Input(T value, T target)
{
    this->error[2] = this->error[1];
    this->error[1] = this->error[0];
    this->error[0] = target - value;
    this->output += this->config.gains.kp * (this->error[0] - this->error[1]) + this->config.gains.ki * this->error[0] + this->config.gains.kd * (this->error[0] - 2 * this->error[1] + this->error[2]) / this->config.dt;
    if(this->config.limits.enabled) this->output = std::clamp(this->output, this->config.limits.min, this->config.limits.max);
}

template class IPIDController<float>;
template class IPIDController<double>;
template class Pos_PIDController<float>;
template class Pos_PIDController<double>;
template class Vel_PIDController<float>;
template class Vel_PIDController<double>;
