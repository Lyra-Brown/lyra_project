#ifndef CAN_TOOL_HPP
#define CAN_TOOL_HPP

#include <cstdint>
#include "lyra_lib/visibility_control.h"

namespace CAN_tool
{
    union LYRA_LIB_PUBLIC CAN_UNION
    {
        uint8_t data[8];
        double d;
        float f[2];
        int64_t i64;
        uint64_t u64;
        int32_t i32[2];
        uint32_t u32[2];
        int16_t i16[4];
        uint16_t u16[4];
        int8_t i8[8];
        uint8_t u8[8];
    };
}

#endif // CAN_TOOL_HPP