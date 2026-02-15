#include "lyra_lib/utils.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace lyra_lib 
{
    static bool g_debug_enable = false;

    void set_debug_print(bool enable) 
    {
        g_debug_enable = enable;
    }

    bool is_debug_print_enabled() 
    {
        return g_debug_enable;
    }

    int32_t DebugPrint(const char* format, ...) 
    {
        if (!g_debug_enable) 
        {
            return -1; // Debug print is disabled, return -1 to indicate no output
        }

        va_list args;
        va_start(args, format);
        int32_t result = vprintf(format, args);
        va_end(args);
        return result;
    }
}