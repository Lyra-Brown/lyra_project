#include "lyra_lib/omni_drive_kinematics.hpp"

#include <cmath>
#include "lyra_lib/math_utils.hpp"

OmniDriveKinematics::OmniDriveKinematics(float wheel_radius, float* from_center_distance, float* robot_yaw, float* wheel_angles, uint8_t wheel_count, float* world_x_vel, float* world_y_vel, float* robot_rot_vel)
    : wheel_radius(wheel_radius),
      wheel_count(wheel_count),
      wheel_angles(wheel_angles),
      from_center_distance(from_center_distance),
      robot_yaw(robot_yaw),
      world_x_vel(world_x_vel),
      world_y_vel(world_y_vel),
      robot_rot_vel(robot_rot_vel)
{
}

float OmniDriveKinematics::get_wheel_omega(uint8_t wheel_identifier)
{
    output_wheel_omega_ = (1.0f / wheel_radius) * 
    ( 
        - std::sin(*robot_yaw + wheel_angles[wheel_identifier]) * (*world_x_vel) + 
        std::cos(*robot_yaw + wheel_angles[wheel_identifier]) * (*world_y_vel) + 
        (*robot_rot_vel) * from_center_distance[wheel_identifier]
    );

    return output_wheel_omega_;
}