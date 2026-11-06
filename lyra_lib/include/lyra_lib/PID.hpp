#ifndef PID_HPP
#define PID_HPP

#include "lyra_lib/visibility_control.h"
#include <cstdint>

template <typename T>
struct PIDGains
{
    T kp;
    T ki;
    T kd;
};

template <typename T>
struct PIDLimits
{
    T min;
    T max;
    bool enabled = false;
};

template <typename T>
struct PIDConfig
{
    PIDGains<T> gains;
    PIDLimits<T> limits;
    T dt;
};

template <typename T>
class IPIDController
{
public:
    ~IPIDController() = default;
    IPIDController() = default;
    IPIDController(T kp_, T ki_, T kd_, T dt_) { config.gains = {kp_, ki_, kd_}; config.dt = dt_; }
    IPIDController(T kp_, T ki_, T kd_) { config.gains = {kp_, ki_, kd_}; }
    void setGains(T kp_, T ki_, T kd_) { config.gains = {kp_, ki_, kd_}; }
    void setDt(T dt_) { config.dt = dt_; }
    void setLimits(T min_, T max_) { config.limits = {min_, max_, true}; }
    void limitsEnabled(bool enabled) { config.limits.enabled = enabled; }
    void toggleLimits() { config.limits.enabled = !config.limits.enabled; }
    T update(T value, T target);
    virtual void refresh() = 0;
    virtual void Input(T value, T target) = 0;
    T Output() const { return output; }

protected:
    PIDConfig<T> config;
    T output = 0;
    T error[3] = {0};
};

template <typename T = double>
class LYRA_LIB_PUBLIC Pos_PIDController : public IPIDController<T>
{
public:
    void refresh() override;
    void Input(T value, T target) override;
    void setIntegralLimits(T min_, T max_) { ie_limits = {min_, max_, true}; }
    void IntegralLimitsEnabled(bool enabled) { ie_limits.enabled = enabled; }
    void toggleIntegralLimits() { ie_limits.enabled = !ie_limits.enabled; }
private:
    T ie = 0;
    PIDLimits<T> ie_limits;
};

template <typename T = double>
class LYRA_LIB_PUBLIC Vel_PIDController : public IPIDController<T>
{
public:
    void refresh() override;
    void Input(T value, T target) override;
};
#endif // PID_HPP
