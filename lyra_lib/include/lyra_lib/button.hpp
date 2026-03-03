#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

class button
{
public:
    button(std::function<void(void)> func) : func(func) {}

    void once(bool flag)
    {
        if (!past && flag)
        {
            func();
        }
        past = flag; // 状態更新
    }

private:
    std::function<void(void)> func;
    bool past = false; // 前回の押下状態
};

class mode_swap
{
public:
    mode_swap(std::function<void(void)> func0, std::function<void(void)> func1, bool& mode)
     : func{func0, func1}, mode(mode) {};

    void go()
    {
        if(mode == 0)
        {
            func[0]();

        }else
        {
            func[1]();
        }
    }


private:
    std::function<void(void)> func[2];
    bool& mode;
};

inline void nothing(){};
#endif