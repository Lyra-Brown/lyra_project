#ifndef OMNI_DRIVE_KINEMATICS_HPP
#define OMNI_DRIVE_KINEMATICS_HPP


#include "aramr_lib/visibility_control.h"
#include <array>
#include <cstdint>


class ARAMR_LIB_PUBLIC OmniDriveKinematics 
{
    public:
        OmniDriveKinematics(float wheel_radius, float robot_radius, float* robot_yaw, float* wheel_angles, uint8_t wheel_count);

        void set_robot_max_velocity(float max_velocity);
        void set_robot_rot_velocity(float rot_velocity);
        float get_wheel_vel(uint8_t wheel_identifier);

    private:
        const float robot_radius_;
        const float wheel_radius_;
        const uint8_t wheel_count_;
        const float* wheel_angles_;

        float robot_max_velocity_ = 10.0; // [m/s]
        float robot_rot_vel_ = 2.0; // [rad/s]
        float wheel_max_omega_ =  0; // [rad/s]
        float output_wheel_omega_ = 0.0; // [rad/s]
        float* robot_yaw_;
};


#endif // OMNI_DRIVE_KINEMATICS_HPP