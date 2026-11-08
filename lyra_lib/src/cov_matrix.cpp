#include "lyra_lib/cov_matrix.hpp"

template<typename T, int size>
Eigen::Matrix<T, size, size> cov_matrix<T, size>::update(const Eigen::Matrix<T, size, 1> &new_data)
{
    for (int i = 0; i < size; ++i)
    {
        matrix_(i, i) = disp[i].update(new_data(i));
    }
    int index = 0;
    for(int i = 0; i < size-1; ++i)
    {
        for(int j = i+1; j < size; ++j)
        {
            matrix_(i, j) = cov[index++].update(new_data(i), new_data(j));
            matrix_(j, i) = matrix_(i, j);
        }
    }
    return matrix_;
}
