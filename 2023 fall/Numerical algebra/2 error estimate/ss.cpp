#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "eigen-3.4.0/Eigen/Dense"

#include "function.h"

using namespace Eigen;

MatrixXd kgenerating_special_matrix(int n)
{
    MatrixXd A = MatrixXd::Zero(n, n);

    for (int i = 0; i < n - 1; i++)
    {
        A(i, i) = 2;
        A(i, i + 1) = -1;
        A(i + 1, i) = -1;
    }
    A(n - 1, n - 1) = 2;
    return A;
}

int main()
{
    MatrixXd A = kgenerating_special_matrix(10);
    VectorXi b = VectorXi::Zero(10);
    cholesky_decomp(A);
    std::cout << "A = " << std::endl;
    std::cout << A << std::endl;
    std::cout << "b = " << std::endl;
    std::cout << b << std::endl;

    return 0;
}