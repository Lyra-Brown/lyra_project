#ifndef PID_HPP
#define PID_HPP

#include "lyra_lib/visibility_control.h"
#include "lyra_lib/limiter.hpp"
#include <cstdint>

template <typename T>
struct PIDGains
{
    T kp = 0;
    T ki = 0;
    T kd = 0;
};


template <typename T>
struct PIDConfig
{
    PIDGains<T> gains;
    T dt = 1e-3;
};

template <typename T>
class PIDControllerBase
{
public:
    virtual ~PIDControllerBase() = default;
    PIDControllerBase() = default;
    PIDControllerBase(T kp_, T ki_, T kd_, T dt_);
    PIDControllerBase(T kp_, T ki_, T kd_);
    void setGains(T kp_, T ki_, T kd_);
    void setDt(T dt_);
    void setLimits(T min_, T max_);
    void limitsEnabled(bool enabled);
    void toggleLimits();
    T update(T value, T target);
    virtual void refresh() = 0;
    T Output() const { return output; }

protected:
    virtual void Input(T value, T target) = 0;
    PIDConfig<T> config;
    Limiter<T> limiter;
    T output = 0;
    T error[3] = {0};
};

template <typename T = double>
class LYRA_LIB_PUBLIC Pos_PIDController : public PIDControllerBase<T>
{
public:
    void refresh() override;
    void Input(T value, T target) override;
    void setIntegralLimits(T min_, T max_);
    void IntegralLimitsEnabled(bool enabled);
    void toggleIntegralLimits();
private:
    T ie = 0;
    Limiter<T> integralLimiter;
};

template <typename T = double>
class LYRA_LIB_PUBLIC Vel_PIDController : public PIDControllerBase<T>
{
public:
    void refresh() override;
    void Input(T value, T target) override;
};
#endif // PID_HPP
