#ifndef OMNI_DRIVE_KINEMATICS_HPP
#define OMNI_DRIVE_KINEMATICS_HPP


#include "lyra_lib/visibility_control.h"
#include <array>
#include <cstdint>
#include "lyra_lib/math_utils.hpp"


class LYRA_LIB_PUBLIC OmniDriveKinematics 
{
    public:
        OmniDriveKinematics(float* wheel_radius, float* from_center_distance, 
                            float& robot_yaw, float* wheel_angles, 
                            float& world_x_vel, float& world_y_vel, float& robot_rot_vel, 
                            float* enc_wheel_omega = nullptr, Coordinate2d* robot_pose = nullptr
                            );

        void get_robot_vel();
        void get_robot_pose();
        float get_wheel_omega(uint8_t wheel_identifier);

    private:
        const float* wheel_radius;
        const float* wheel_angles;
        const float* from_center_distance;
        const float* enc_wheel_omega;

        Coordinate2d* robot_pose;

        Eigen::Matrix<double, WHEEL_COUNT, 3> J;
        Eigen::Matrix<double, 3, WHEEL_COUNT> J_local;
        Eigen::Matrix<double, 3, WHEEL_COUNT> J_local_inv;
        Eigen::Matrix<double, WHEEL_COUNT, 1> wheel_omega;
        Coordinate2d calic_robot_world_vel;

        float output_wheel_omega_ = 0.0; // [rad/s]
        float& robot_yaw;
        float& world_x_vel;
        float& world_y_vel;
        float& robot_rot_vel;
};


#endif // OMNI_DRIVE_KINEMATICS_HPP