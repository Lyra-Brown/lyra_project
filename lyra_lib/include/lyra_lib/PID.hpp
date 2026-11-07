#ifndef PID_HPP
#define PID_HPP

#include "lyra_lib/visibility_control.h"
#include "lyra_lib/limiter.hpp"
#include <cstdint>

template <typename T>
struct pid_gains
{
    T kp = 0;
    T ki = 0;
    T kd = 0;
};


template <typename T>
struct pid_config
{
    pid_gains<T> gains;
    T dt = 1e-3;
};

template <typename T>
class pid_controller_base
{
public:
    virtual ~pid_controller_base() = default;
    pid_controller_base() = default;
    pid_controller_base(T kp_, T ki_, T kd_, T dt_);
    pid_controller_base(T kp_, T ki_, T kd_);
    void set_gains(T kp_, T ki_, T kd_);
    void set_dt(T dt_);
    void set_limits(T min_, T max_);
    void limits_enabled(bool enabled);
    void toggle_limits();
    T update(T value, T target);
    virtual void refresh() = 0;
    T output_value() const { return output; }

protected:
    virtual void input(T value, T target) = 0;
    pid_config<T> config;
    Limiter<T> limiter;
    T output = 0;
    T error[3] = {0};
};

template <typename T = double>
class LYRA_LIB_PUBLIC pos_pid_controller : public pid_controller_base<T>
{
public:
    void refresh() override;
    void input(T value, T target) override;
    void set_integral_limits(T min_, T max_);
    void integral_limits_enabled(bool enabled);
    void toggle_integral_limits();
private:
    T ie = 0;
    Limiter<T> integral_limiter;
};

template <typename T = double>
class LYRA_LIB_PUBLIC vel_pid_controller : public pid_controller_base<T>
{
public:
    void refresh() override;
    void input(T value, T target) override;
};
#endif // PID_HPP
