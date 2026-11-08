#ifndef CONV_MATRIX_HPP
#define CONV_MATRIX_HPP

#include <Eigen/Core>
#include <Eigen/Dense>
#include "lyra_lib/dispersion.hpp"
#include "lyra_lib/covariance.hpp"
#include "lyra_lib/dispersion.hpp"

template<typename T, int size>
class cov_matrix
{
public:
    cov_matrix() = default;
    ~cov_matrix() = default;
    Eigen::Matrix<T, size, size> update(const Eigen::Matrix<T, size, 1> &new_data);
    Eigen::Matrix<T, size, size> get_matrix() const { return matrix_; }
    T get_element(int row, int col) const { return matrix_(row, col); }

private:
    Eigen::Matrix<T, size, size> matrix_ = Eigen::Matrix<T, size, size>::Zero(size, size);
    dispersion<T> disp[size];
    covariance<T> cov[(size * size - size) / 2];
};

#endif // CONV_MATRIX_HPP
