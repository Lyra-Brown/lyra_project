#ifndef OMNI_DRIVE_KINEMATICS_HPP
#define OMNI_DRIVE_KINEMATICS_HPP


#include "lyra_lib/visibility_control.h"
#include <array>
#include <cstdint>


class LYRA_LIB_PUBLIC OmniDriveKinematics 
{
    public:
        OmniDriveKinematics(float wheel_radius, float* from_center_distance, float* robot_yaw, float* wheel_angles, uint8_t wheel_count, float* world_x_vel, float* world_y_vel, float* robot_rot_vel);

        float get_wheel_omega(uint8_t wheel_identifier);

    private:
        const float wheel_radius;
        const uint8_t wheel_count;
        const float* wheel_angles;
        const float* from_center_distance;

        float output_wheel_omega_ = 0.0; // [rad/s]
        float* robot_yaw;
        float* world_x_vel;
        float* world_y_vel;
        float* robot_rot_vel;
};


#endif // OMNI_DRIVE_KINEMATICS_HPP