#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "lyra_lib/visibility_control.h"
#include <cstdint>
#include "lyra_lib/math_utils.hpp"


constexpr uint8_t WHEEL_COUNT = 4;
constexpr float cycle_time = static_cast<float>(10.0 * MILLI);

#endif // CONFIG_HPP