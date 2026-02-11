#ifndef PID_HPP
#define PID_HPP

#include "lyra_lib/visibility_control.h"


class PID 
{
    public:
        PID(double Kp, double Ki, double Kd);
    
        void Input(double target, double value);
        double Output();
        void refresh();
        void set_limits(float min, float max);
    
    private:
        double Kp;
        double Ki;
        double Kd;
        
        double e[3] = {0}; 
        double u = 0;
        bool limits_enabled = false;
        float min_limit = 0;
        float max_limit = 0;
};

#endif // PID_HPP