#include "lyra_lib/PID.hpp"

#include <cstdint>
#include <algorithm>
#include <stdexcept>

template <typename T>
PIDControllerBase<T>::PIDControllerBase(T kp_, T ki_, T kd_, T dt_)
{
    config.gains = {kp_, ki_, kd_};
    setDt(dt_);
}

template <typename T>
PIDControllerBase<T>::PIDControllerBase(T kp_, T ki_, T kd_)
{
    config.gains = {kp_, ki_, kd_};
}

template <typename T>
void PIDControllerBase<T>::setGains(T kp_, T ki_, T kd_)
{
    config.gains = {kp_, ki_, kd_};
}

template <typename T>
void PIDControllerBase<T>::setDt(T dt_)
{
    if(dt_ <= 0)
    {
        throw std::invalid_argument("dt must be greater than 0");
    }
    config.dt = dt_;
}

template <typename T>
void PIDControllerBase<T>::setLimits(T min_, T max_)
{
    limiter.setLimits(min_, max_);
}

template <typename T>
void PIDControllerBase<T>::limitsEnabled(bool enabled)
{
    limiter.enableLimits(enabled);
}

template <typename T>
void PIDControllerBase<T>::toggleLimits()
{
    limiter.toggleLimits();
}

template <typename T>
T PIDControllerBase<T>::update(T value, T target)
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
    ie = integralLimiter.setValue(ie);
    this->output = this->config.gains.kp * this->error[0] + this->config.gains.ki * ie + this->config.gains.kd * de;
    this->output = this->limiter.setValue(this->output);
    this->error[1] = this->error[0];
}

template <typename T>
void Pos_PIDController<T>::setIntegralLimits(T min_, T max_)
{
    integralLimiter.setLimits(min_, max_);
}

template <typename T>
void Pos_PIDController<T>::IntegralLimitsEnabled(bool enabled)
{
    integralLimiter.enableLimits(enabled);
}

template <typename T>
void Pos_PIDController<T>::toggleIntegralLimits()
{
    integralLimiter.toggleLimits();
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
    this->output = this->limiter.setValue(this->output);
}

template class PIDControllerBase<float>;
template class PIDControllerBase<double>;
template class Pos_PIDController<float>;
template class Pos_PIDController<double>;
template class Vel_PIDController<float>;
template class Vel_PIDController<double>;
