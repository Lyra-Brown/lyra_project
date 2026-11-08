#ifndef CONV_MATRIX_HPP
#define CONV_MATRIX_HPP

#include <Eigen/Core>
#include <Eigen/Dense>
#include "lyra_lib/dispersion.hpp"
#include "lyra_lib/covariance.hpp"
#include "lyra_lib/dispersion.hpp"
#include "lyra_lib/visibility_control.h"

template<typename T>
class LYRA_LIB_PUBLIC cov_matrix
{
public:
    explicit cov_matrix(int size);
    ~cov_matrix() = default;

    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> update(const Eigen::Matrix<T, Eigen::Dynamic, 1> &new_data);
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> get_matrix() const { return matrix_; }
    T get_element(int row, int col) const { return matrix_(row, col); }

private:
    int size_;
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> matrix_;
    std::vector<dispersion<T>> disp;
    std::vector<covariance<T>> cov;

    void calc_cov(const Eigen::Matrix<T, Eigen::Dynamic, 1> &new_data);
    void calc_disp(const Eigen::Matrix<T, Eigen::Dynamic, 1> &new_data);
};

#endif // CONV_MATRIX_HPP
