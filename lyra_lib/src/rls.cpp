#include "lyra_lib/rls.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace
{
template <typename T>
typename rls_vel<T>::vector make_initial_params(
    const T* initial_params,
    Eigen::Index parameter_count)
{
    if (initial_params == nullptr || parameter_count <= 0)
    {
        throw std::invalid_argument(
            "rls_vel: initial_params must be non-null and parameter_count must be positive");
    }

    return Eigen::Map<const typename rls_vel<T>::vector>(
        initial_params,
        parameter_count);
}
} // namespace

template <typename T>
rls_vel<T>::rls_vel(
    const vector& initial_params,
    T forgetting_factor,
    T initial_covariance)
    : parameters(initial_params),
      covariance(
          Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Identity(
              initial_params.size(),
              initial_params.size())
          * initial_covariance),
      forget_factor(std::clamp(
          forgetting_factor,
          static_cast<T>(1.0e-6),
          static_cast<T>(1.0))),
      initial_covariance(initial_covariance)
{
    if (parameters.size() == 0)
    {
        throw std::invalid_argument(
            "rls_vel: initial_params must not be empty");
    }
}

template <typename T>
rls_vel<T>::rls_vel(
    const T* initial_params,
    Eigen::Index parameter_count,
    T forgetting_factor,
    T initial_covariance)
    : rls_vel<T>(
          make_initial_params<T>(initial_params, parameter_count),
          forgetting_factor,
          initial_covariance)
{
}

template <typename T>
void rls_vel<T>::set_clipping_threshold(T threshold)
{
    clipping_threshold = std::abs(threshold);
}

template <typename T>
void rls_vel<T>::set_covariance_reset_flag(bool flag)
{
    covariance_reset_flag = flag;
}

template <typename T>
void rls_vel<T>::update(
    T actual_value,
    const vector& true_value_labels)
{
    if (true_value_labels.size() != parameters.size())
    {
        throw std::invalid_argument(
            "rls_vel: true_value_labels size must match the parameter count");
    }

    const T denominator =
        forget_factor
        + true_value_labels.dot(covariance * true_value_labels);
    if (!std::isfinite(denominator)
        || std::abs(denominator) < static_cast<T>(1e-12))
    {
        return;
    }

    const vector gain =
        covariance * true_value_labels / denominator;
    const T error =
        actual_value - true_value_labels.dot(parameters);
    parameters += gain * error;
    covariance =
        (covariance - gain * true_value_labels.transpose() * covariance)
        / forget_factor;

    for (Eigen::Index i = 0; i < covariance.rows(); ++i)
    {
        for (Eigen::Index j = 0; j < covariance.cols(); ++j)
        {
            if (!std::isfinite(covariance(i, j)) && i != j)
            {
                covariance(i, j) = 0.0;
            }
        }

        if (!std::isfinite(covariance(i, i)))
        {
            covariance(i, i) = initial_covariance;
        }
    }

    if (covariance_reset_flag)
    {
        for (Eigen::Index i = 0; i < covariance.rows(); ++i)
        {
            covariance(i, i) = std::clamp(
                covariance(i, i),
                -clipping_threshold,
                clipping_threshold);
        }
        return;
    }

    for (Eigen::Index i = 0; i < covariance.rows(); ++i)
    {
        if (std::abs(covariance(i, i)) > clipping_threshold)
        {
            covariance.setZero();
            covariance.diagonal().setConstant(initial_covariance);
            return;
        }
    }
}

template <typename T>
typename rls_vel<T>::vector rls_vel<T>::get_parameters() const
{
    return parameters;
}

template class rls_vel<float>;
template class rls_vel<double>;
