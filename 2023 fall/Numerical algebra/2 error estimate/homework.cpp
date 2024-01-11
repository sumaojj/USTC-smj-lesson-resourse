#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "eigen-3.4.0/Eigen/Dense"
#include "function.h"
using namespace Eigen;

int main()
{
    for (int i = 5; i <= 20; i++)
    {
        MatrixXd A = generating_Hilbert_matrix(i);

        std::cout << "size of Matrix=" << i << "\t"
                  << "condition number by infinity norm of Hilbert matrix A = " << compute_infty_norm(A) * compute_A_inverse_infty_norm(A) << std::endl;
    }

    std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
    for (int i = 5; i <= 30; i++)
    {
        MatrixXd A = generating_special_matrix(i);

        VectorXd x = VectorXd::Random(i);

        VectorXd b = A * x;

        VectorXd x_est = solve_linear_equations(A, b);

        VectorXd r = x_est - x;

        std::cout << "size of Matrix=" << i << "\t"
                  << "Relative error of estimate = " << compute_infty_norm(A) * compute_A_inverse_infty_norm(A) * r.lpNorm<Infinity>() / b.lpNorm<Infinity>() << std::endl
                  << "real relative error = " << (r.lpNorm<Infinity>()) / (x.lpNorm<Infinity>()) << std::endl;
    }

    return 0;
}