#include "aramr_lib/PID.hpp"


PID::PID(double Kp, double Ki, double Kd) : Kp(Kp), Ki(Ki), Kd(Kd) {}

void PID::Input(double target, double value) 
{
    e[2] = e[1];
    e[1] = e[0];
    e[0] = target - value;

    u += Kp * (e[0] - e[1]) + Ki * e[0] + Kd * (e[0] - 2 * e[1] + e[2]);
    if (limits_enabled) 
    {
        if (u > max_limit) 
        {
            u = max_limit;
        } 
        else if (u < min_limit) 
        {
            u = min_limit;
        }
    }

}

double PID::Output() 
{
    return u;
}

void PID::refresh() 
{
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
    u = 0;
}

void PID::set_limits(float min, float max) 
{
    min_limit = min;
    max_limit = max;
    limits_enabled = true;
}