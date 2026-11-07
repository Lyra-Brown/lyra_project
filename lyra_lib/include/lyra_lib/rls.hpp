#ifndef LYRA_LIB_RLS_HPP
#define LYRA_LIB_RLS_HPP

#include "lyra_lib/visibility_control.h"

#include "Eigen/Dense"

template <typename T = double>
class LYRA_LIB_PUBLIC rls_vel
{
public:
    using vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;

    rls_vel(
        const vector& initial_params,
        T forgetting_factor = static_cast<T>(0.8),
        T initial_covariance = static_cast<T>(1000.0));

    rls_vel(
        const T* initial_params,
        Eigen::Index parameter_count,
        T forgetting_factor = static_cast<T>(0.8),
        T initial_covariance = static_cast<T>(1000.0));

    void set_clipping_threshold(T threshold);
    void set_covariance_reset_flag(bool flag);

    void update(T actual_value, const vector& true_value_labels);
    vector get_parameters() const;

private:
    vector parameters;
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> covariance;
    T forget_factor;
    T clipping_threshold = static_cast<T>(1e5);
    T initial_covariance;
    bool covariance_reset_flag = true;
};

#endif // LYRA_LIB_RLS_HPP
