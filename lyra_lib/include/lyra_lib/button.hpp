#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <cstdint>

namespace lura::input
{

enum class ButtonState : uint8_t
{
    DEFAULT,
    UP_EDGE,
    DOWN_EDGE,
    EDGE,
    BUTTON_STATE_COUNT
};

class Button
{
public:
    Button();
    void update(bool pressed_)
    {
        wasPressed = pressed;
        pressed = pressed_;
    };
    bool isPressed(ButtonState state) const
    {
        switch (state)
        {
        case ButtonState::DEFAULT:
            return pressed;
        case ButtonState::UP_EDGE:
            return !pressed && wasPressed;
        case ButtonState::DOWN_EDGE:
            return pressed && !wasPressed;
        case ButtonState::EDGE:
            return pressed != wasPressed;
        default:
            return false;
        }
    };

private:
    uint8_t state;
    bool pressed = false;
    bool wasPressed = false;
};

} // namespace lura::input

#endif