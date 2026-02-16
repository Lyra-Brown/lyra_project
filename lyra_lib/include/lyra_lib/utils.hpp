#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

#include "lyra_lib/visibility_control.h"

namespace lyra_lib
{
    LYRA_LIB_PUBLIC void set_debug_print(bool enable);
    LYRA_LIB_PUBLIC bool is_debug_print_enabled();
    LYRA_LIB_PUBLIC int32_t DebugPrint(const char* format, ...);
}

namespace enum_utils
{
    enum LYRA_LIB_PUBLIC SteeringMode
    {
        UNDEFINED = 0,
        OMNIDIRECTIONAL,
        INDEPENDENT_STEERING
    };
}

#endif // UTILS_HPP