#include "lyra_lib/omni_drive_kinematics.hpp"

#include <cmath>
#include "lyra_lib/math_utils.hpp"

OmniDriveKinematics::OmniDriveKinematics(float wheel_radius, float robot_radius, float* robot_yaw, float* wheel_angles, uint8_t wheel_count)
    : robot_radius_(robot_radius),
      wheel_radius_(wheel_radius),
      wheel_count_(wheel_count),
      wheel_angles_(wheel_angles),
      robot_yaw_(robot_yaw)
{
}

void OmniDriveKinematics::set_robot_max_velocity(float max_velocity)
{
    robot_max_velocity_ = max_velocity;
}

void OmniDriveKinematics::set_robot_rot_velocity(float rot_velocity)
{
    robot_rot_vel_ = rot_velocity;
}

float OmniDriveKinematics::get_wheel_omega(uint8_t wheel_identifier)
{
    output_wheel_omega_ = (1.0f / wheel_radius_) * 
    ( 
        - std::sin(*robot_yaw_ + wheel_angles_[wheel_identifier]) * robot_max_velocity_ + 
        std::cos(*robot_yaw_ + wheel_angles_[wheel_identifier]) * robot_max_velocity_ + 
        robot_rot_vel_ * robot_radius_
    );
    
    return output_wheel_omega_;
}