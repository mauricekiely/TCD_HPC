#include "matrix.h"
#include <iostream>

using namespace HPC;

int main(){
    // Define two matrices with initial values.
    Matrix<int> matrix1(2, 2); // 2x2 matrix
    Matrix<int> matrix2(2, 2); // 2x2 matrix

    // Populate matrix1
    matrix1(0, 0) = 1; matrix1(0, 1) = 2;
    matrix1(1, 0) = 3; matrix1(1, 1) = 4;

    // Populate matrix2
    matrix2(0, 0) = 5; matrix2(0, 1) = 6;
    matrix2(1, 0) = 7; matrix2(1, 1) = 8;

    // Perform matrix addition
    Matrix<int> result = matrix1 + matrix2;

    // Print the result
    std::cout << "Result of matrix addition:\n" << result;

    return 0;
}

