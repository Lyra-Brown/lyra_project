#include "lyra_lib/omni_drive_kinematics.hpp"

#include <cmath>
#include "lyra_lib/math_utils.hpp"
#include "lyra_lib/config.hpp"

OmniDriveKinematics::OmniDriveKinematics(float* wheel_radius, float* from_center_distance, 
                                         float& robot_yaw, float* wheel_angles,
                                         float& world_x_vel, float& world_y_vel, float& robot_rot_vel,
                                         float* enc_wheel_omega, Coordinate2d* robot_pose
                                        )
    : wheel_radius(wheel_radius), wheel_angles(wheel_angles), from_center_distance(from_center_distance), 
      enc_wheel_omega(enc_wheel_omega), robot_pose(robot_pose), robot_yaw(robot_yaw), world_x_vel(world_x_vel), 
      world_y_vel(world_y_vel), robot_rot_vel(robot_rot_vel)
{
    // Initialize the Jacobian matrix J
    for (size_t i = 0; i < WHEEL_COUNT; i++) {
        J_local(i, 0) = -std::sin(wheel_angles[i]);
        J_local(i, 1) = std::cos(wheel_angles[i]);
        J_local(i, 2) = from_center_distance[i];
    }
    J_local_inv = J_local.completeOrthogonalDecomposition().pseudoInverse();
}

void OmniDriveKinematics::get_robot_vel()
{
    if(enc_wheel_omega == nullptr || wheel_radius == nullptr) return;
    
    double vx_robot = 0, vy_robot = 0, vtheta = 0;
    for(size_t j = 0; j < WHEEL_COUNT; j++) {
        double v_wheel = wheel_radius[j] * enc_wheel_omega[j];
        vx_robot += J_local_inv(0, j) * v_wheel;
        vy_robot += J_local_inv(1, j) * v_wheel;
        vtheta   += J_local_inv(2, j) * v_wheel;
    }
    calic_robot_world_vel.angle = vtheta;
    calic_robot_world_vel.position.x() = vx_robot * std::cos(robot_yaw) - vy_robot * std::sin(robot_yaw);
    calic_robot_world_vel.position.y() = vx_robot * std::sin(robot_yaw) + vy_robot * std::cos(robot_yaw);
}

void OmniDriveKinematics::get_robot_pose()
{
    if(robot_pose == nullptr) return;

    robot_pose->position.x() += calic_robot_world_vel.position.x() * cycle_time;
    robot_pose->position.y() += calic_robot_world_vel.position.y() * cycle_time;
    robot_pose->angle += calic_robot_world_vel.angle * cycle_time;
}

float OmniDriveKinematics::get_wheel_omega(uint8_t wheel_identifier)
{
    if(wheel_radius == nullptr || wheel_identifier >= WHEEL_COUNT 
       || wheel_radius[wheel_identifier] <= 0.0f) 
       return 0.0f;

    output_wheel_omega_ = (1.0f / wheel_radius[wheel_identifier]) * 
    ( 
        - std::sin(robot_yaw + wheel_angles[wheel_identifier]) * (world_x_vel) + 
        std::cos(robot_yaw + wheel_angles[wheel_identifier]) * (world_y_vel) + 
        (robot_rot_vel) * from_center_distance[wheel_identifier]
    );

    return output_wheel_omega_;
}