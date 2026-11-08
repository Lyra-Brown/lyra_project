#include "lyra_lib/cov_matrix.hpp"

template<typename T>
cov_matrix<T>::cov_matrix(int size) : size_(size), matrix_(Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>::Zero(size, size)), disp(size), cov((size * (size - 1)) / 2) {}

template<typename T>
Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> cov_matrix<T>::update(const Eigen::Matrix<T, Eigen::Dynamic, 1> &new_data)
{
    calc_disp(new_data);
    calc_cov(new_data);
    return matrix_;
}

template<typename T>
void cov_matrix<T>::calc_cov(const Eigen::Matrix<T, Eigen::Dynamic, 1> &new_data)
{
    int index = 0;
    for(int i = 0; i < size_ - 1; ++i)
    {
        for(int j = i + 1; j < size_; ++j)
        {
            matrix_(i, j) = cov[index++].update(new_data(i), new_data(j));
            matrix_(j, i) = matrix_(i, j);
        }
    }
}

template<typename T>
void cov_matrix<T>::calc_disp(const Eigen::Matrix<T, Eigen::Dynamic, 1> &new_data)
{
    for (int i = 0; i < size_; ++i)
    {
        matrix_(i, i) = disp[i].update(new_data(i));
    }
}
