#ifndef LIMITER_HPP
#define LIMITER_HPP

#include <algorithm>
#include "lyra_lib/visibility_control.h"

template <typename T = double>
class LYRA_LIB_PUBLIC Limiter 
{
public:
    Limiter() = default;
    ~Limiter() = default;

    Limiter(T value, T min, T max) 
        : ownedValue(value), ownedMin(min), ownedMax(max),
          valPtr(&ownedValue), minPtr(&ownedMin), maxPtr(&ownedMax) {}

    Limiter(T* value, T* min, T* max) 
        : valPtr(value), minPtr(min), maxPtr(max) {}

    Limiter(const Limiter& other) 
        : ownedValue(other.ownedValue), ownedMin(other.ownedMin), ownedMax(other.ownedMax),
          valPtr(other.valPtr == &other.ownedValue ? &ownedValue : other.valPtr),
          minPtr(other.minPtr == &other.ownedMin ? &ownedMin : other.minPtr),
          maxPtr(other.maxPtr == &other.ownedMax ? &ownedMax : other.maxPtr) {}

    void setLimits(T min, T max)
    {
        *minPtr = min;
        *maxPtr = max;
        limitsEnabled = true;
    }
    void setMin(T min)
    {
        *minPtr = min;
        limitsEnabled = true;
    }
    void setMax(T max)
    {
        *maxPtr = max;
        limitsEnabled = true;
    }

    T setValue(T v)
    {
        if (limitsEnabled)
        {
            *valPtr = std::clamp(v, *minPtr, *maxPtr);
        }
        else
        {
            *valPtr = v;
        }
        return *valPtr;
    }

    void update()
    {
        if (limitsEnabled)
        {
            *valPtr = std::clamp(*valPtr, *minPtr, *maxPtr);
        }
    }

    void enableLimits(bool enable) { limitsEnabled = enable; }
    void toggleLimits() { limitsEnabled = !limitsEnabled; }

    T getValue() const { return *valPtr; }
    T getMin()   const { return *minPtr; }
    T getMax()   const { return *maxPtr; }

private:
    T ownedValue{0};
    T ownedMin{0};
    T ownedMax{0};

    T* valPtr = &ownedValue;
    T* minPtr = &ownedMin;
    T* maxPtr = &ownedMax;

    bool limitsEnabled = false;

};

#endif // LIMITER_HPP
