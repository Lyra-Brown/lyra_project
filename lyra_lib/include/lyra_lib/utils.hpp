#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>


namespace lyra_lib
{
    void set_debug_print(bool enable);
    bool is_debug_print_enabled();
    int32_t DebugPrint(const char* format, ...);
}


#endif // UTILS_HPP