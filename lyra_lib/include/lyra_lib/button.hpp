#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <cstdint>
#include "lyra_lib/visibility_control.h"

namespace lura::input
{

enum class LYRA_LIB_PUBLIC_TYPE button_state : uint8_t
{
    default_state,
    up_edge,
    down_edge,
    edge,
    button_state_count
};

class LYRA_LIB_PUBLIC button
{
public:
    button();
    void update(bool pressed_)
    {
        was_pressed = pressed;
        pressed = pressed_;
    };
    bool is_pressed(button_state state = button_state::default_state) const
    {
        switch (state)
        {
        case button_state::default_state:
            return pressed;
        case button_state::up_edge:
            return !pressed && was_pressed;
        case button_state::down_edge:
            return pressed && !was_pressed;
        case button_state::edge:
            return pressed != was_pressed;
        default:
            return false;
        }
    };

private:
    uint8_t state;
    bool pressed = false;
    bool was_pressed = false;
};

} // namespace lura::input

#endif