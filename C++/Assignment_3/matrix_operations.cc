#include "matrix_operations.h"

/**
 * @brief Function to take in a Square matrix and vector/matrix to
 *          perform gaussian elimination to find inverse or solve
 *          system of linear equations
 * 
 * @tparam T number type of Matrix A
 * @tparam U number type of Vector/Matrix B
 * @param A Square Matrix to solve linear equations or get inverse
 * @param B identity matrix of vector to solve for
 * @return HPC::Matrix<double> solution vector x or inverse of A
 */
template <Number T, Number U>
HPC::Matrix<double> gaussjordan(HPC::Matrix<T> const& A, HPC::Matrix<U> const& B) {
    // Get necessary Dimensions
    std::size_t A_rows = A.get_num_rows();
    std::size_t B_cols = B.get_num_cols();

    if (A.get_num_rows() != A.get_num_cols()) {
        throw std::string("Matrix A is not square");
    }

    // Create Dummy matrices and populate
    HPC::Matrix<double> A_copy(A_rows, A_rows);
    HPC::Matrix<double> B_copy(A_rows, B_cols);

    for (std::size_t i = 0; i < A_rows; i++) {
        for (std::size_t j = 0; j < A_rows; j++) {
            A_copy(i, j) = A(i, j);
        }
        for (std::size_t j = 0; j < B_cols; j++) {
            B_copy(i, j) = B(i, j);
        }
    }

    // Perform Gauss-Jordan on copy objects
    for (std::size_t i = 0; i < A_rows; ++i) {
        double diag = A_copy(i, i);
        if (diag == 0) {
            throw std::string("Diagonal element is zero, can't compute inverse");
        }
        // Standardise each element on the row
        for (std::size_t j = 0; j <A_rows; ++j) {
            A_copy(i, j) /= diag;
        }
        for (std::size_t j = 0; j <B_cols; ++j) {
            B_copy(i, j) /= diag;
        }

        // Make the non-diagonal elements all zeros
        for (std::size_t k = 0; k < A_rows; ++k) {
            if (k != i) {
                double factor = A_copy(k, i);
                for (std::size_t j = 0; j < A_rows; ++j) {
                    A_copy(k, j) -= factor * A_copy(i, j);
                }
                for (std::size_t j = 0; j < B_cols; ++j) {
                    B_copy(k, j) -= factor * B_copy(i, j);
                }
            }
        }
    }
    return B_copy;
}

template HPC::Matrix<double> gaussjordan<double, double>(const HPC::Matrix<double>&, const HPC::Matrix<double>&);
template HPC::Matrix<double> gaussjordan<int, double>(const HPC::Matrix<int>&, const HPC::Matrix<double>&);
template HPC::Matrix<double> gaussjordan<int, int>(const HPC::Matrix<int>&, const HPC::Matrix<int>&);