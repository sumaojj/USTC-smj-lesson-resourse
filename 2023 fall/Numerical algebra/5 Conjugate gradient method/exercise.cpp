#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include "eigen-3.4.0/Eigen/Dense"
#include "function.cpp"

using namespace Eigen;
clock_t start, end;
int iteration = 0;

void exercise1()
{
    MatrixXd A{generate_1_Matrix(20)};
    VectorXd b{generate_1_Vector(20)};
    VectorXd x0{VectorXd::Zero(19 * 19)};

    start = clock();
    VectorXd x{Conjugate_gradient_method(A, b, x0, 1e-8, iteration)};
    end = clock();

    std::cout << "Exercise 1: Conjugate gradient method" << std::endl;
    std::cout << "x: " << x.transpose() << std::endl;
    std::cout << "Iteration: " << iteration << std::endl;
    std::cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "Error: " << (A * x - b).transpose() << std::endl;
    std::cout << "\n\n\n\n\n";
}

void exercise2()
{
    VectorXi N_list(4);
    N_list << 20, 40, 60, 80;
    for (int N : N_list)
    {
        MatrixXd A{generate_Hilbert_MatrixXd(N)};
        VectorXd b{generate_Hilbert_VectorXd(N)};
        VectorXd x0{VectorXd::Zero(N)};

        start = clock();
        VectorXd x{Conjugate_gradient_method(A, b, x0, 1e-10, iteration)};
        end = clock();

        std::cout << "Exercise 2: Conjugate gradient method" << std::endl;
        std::cout << "N: " << N << std::endl;
        std::cout << "Iteration: " << iteration << std::endl;
        std::cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
        std::cout << "Error: " << (A * x - b).transpose() << std::endl;
        std::cout << "\n\n";
    }
    std::cout << "\n\n\n\n\n";
}

void exercise3()
{
    MatrixXd A(5, 5);
    A << 10, 1, 2, 3, 4,
        1, 9, -1, 2, -3,
        2, -1, 7, 3, -5,
        3, 2, 3, 12, -1,
        4, -3, -5, -1, 15;

    VectorXd b(5);
    b << 12, -27, 14, -17, 12;

    VectorXd x0{VectorXd::Zero(5)};

    start = clock();
    VectorXd x{Conjugate_gradient_method(A, b, x0, 1e-7, iteration)};
    end = clock();

    std::cout << "Exercise 3: Conjugate gradient method" << std::endl;
    std::cout << "Iteration: " << iteration << std::endl;
    std::cout << "Time: " << (double)(end - start) << std::endl;
    std::cout << "Error: " << (A * x - b).transpose() << std::endl;
    std::cout << "\n\n";

    start = clock();
    VectorXd x1{Jacobi_iteration_solve(A, b, 1e-7, iteration)};
    end = clock();

    std::cout << "Exercise 3: Jacobi iteration method" << std::endl;
    std::cout << "Iteration: " << iteration << std::endl;
    std::cout << "Time: " << (double)(end - start) << std::endl;
    std::cout << "Error: " << (A * x - b).transpose() << std::endl;
    std::cout << "\n\n";

    start = clock();
    VectorXd x2{Gauss_Seidel_iteration_solve(A, b, 1e-7, iteration)};
    end = clock();

    std::cout << "Exercise 3: Gauss-Seidel iteration method" << std::endl;
    std::cout << "Iteration: " << iteration << std::endl;
    std::cout << "Time: " << (double)(end - start) << std::endl;
    std::cout << "Error: " << (A * x - b).transpose() << std::endl;
    std::cout << "\n\n";
}