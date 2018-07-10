#include "tensor.hpp"
std::ostream &operator<<(std::ostream &os, const Matrix<3, 3> &matrix)
{
    for (int i = 0; i < Matrix<3, 3>::DIM1; i++) {
        for (int j = 0; j < Matrix<3, 3>::DIM2; j++)
            os << matrix[i][j] << " ";
        os << "\n";
    }
    return os;
}