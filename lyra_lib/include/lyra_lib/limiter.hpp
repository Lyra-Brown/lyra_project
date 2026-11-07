#ifndef LIMITER_HPP
#define LIMITER_HPP

#include <algorithm>
#include "lyra_lib/visibility_control.h"

template <typename T = double>
class LYRA_LIB_PUBLIC limiter
{
public:
    limiter() = default;
    ~limiter() = default;

    limiter(T value, T min, T max)
        : owned_value(value), owned_min(min), owned_max(max),
          value_ptr(&owned_value), min_ptr(&owned_min), max_ptr(&owned_max) {}

    limiter(T* value, T* min, T* max)
        : value_ptr(value), min_ptr(min), max_ptr(max) {}

    limiter(const limiter& other)
        : owned_value(other.owned_value), owned_min(other.owned_min), owned_max(other.owned_max),
          value_ptr(other.value_ptr == &other.owned_value ? &owned_value : other.value_ptr),
          min_ptr(other.min_ptr == &other.owned_min ? &owned_min : other.min_ptr),
          max_ptr(other.max_ptr == &other.owned_max ? &owned_max : other.max_ptr),
          limits_enabled(other.limits_enabled) {}

    void set_limits(T min, T max)
    {
        *min_ptr = min;
        *max_ptr = max;
        limits_enabled = true;
    }
    void set_min(T min)
    {
        *min_ptr = min;
        limits_enabled = true;
    }
    void set_max(T max)
    {
        *max_ptr = max;
        limits_enabled = true;
    }

    T set_value(T value)
    {
        if (limits_enabled)
        {
            *value_ptr = std::clamp(value, *min_ptr, *max_ptr);
        }
        else
        {
            *value_ptr = value;
        }
        return *value_ptr;
    }

    void update()
    {
        if (limits_enabled)
        {
            *value_ptr = std::clamp(*value_ptr, *min_ptr, *max_ptr);
        }
    }

    void enable_limits(bool enable) { limits_enabled = enable; }
    void toggle_limits() { limits_enabled = !limits_enabled; }

    T get_value() const { return *value_ptr; }
    T get_min()   const { return *min_ptr; }
    T get_max()   const { return *max_ptr; }

private:
    T owned_value{0};
    T owned_min{0};
    T owned_max{0};

    T* value_ptr = &owned_value;
    T* min_ptr = &owned_min;
    T* max_ptr = &owned_max;

    bool limits_enabled = false;

};

#endif // LIMITER_HPP
