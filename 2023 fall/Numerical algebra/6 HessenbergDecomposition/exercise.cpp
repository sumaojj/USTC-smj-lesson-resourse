// generate head file guard
#ifndef EXERCISE_CPP
#define EXERCISE_CPP
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function.h"

clock_t start, end;

void exercise1()
{
    std::cout << "exercise 1:" << std::endl;

    // coefficients of polynomial from x^0 to x^n-1
    // set iter
    int iter = 1000000;

    // example 1
    VectorXd a1(4);
    a1 << 3, -5, 1, 1;
    MatrixXd C1 = generate_Companion_Matrix(a1);
    start = clock();
    double lambda1 = power_method(C1, iter);
    end = clock();

    std::cout << "the fist task:" << std::endl;
    std::cout << "iter = " << iter << std::endl;
    std::cout << "lambda1 = " << lambda1 << std::endl;
    std::cout << "time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;

    // example 2
    VectorXd a2(4);
    a2 << 1, -3, 0, 1;
    MatrixXd C2 = generate_Companion_Matrix(a2);
    start = clock();
    double lambda2 = power_method(C2, iter);
    end = clock();

    std::cout << "the second task:" << std::endl;
    std::cout << "iter = " << iter << std::endl;
    std::cout << "lambda2 = " << lambda2 << std::endl;
    std::cout << "time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;

    // example 3
    VectorXd a3(9);
    a3 << -1000, -790, -99902, 79108.9, 9802.08, 10891.01, 208.01, 101, 1;
    MatrixXd C3 = generate_Companion_Matrix(a3);
    start = clock();
    double lambda3 = power_method(C3, iter);
    end = clock();

    std::cout << "the third task:" << std::endl;
    std::cout << "iter = " << iter << std::endl;
    std::cout << "lambda3 = " << lambda3 << std::endl;
    std::cout << "time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
}

void exercise2()
{
    std::cout << "exercise 2:" << std::endl;

    VectorXd x1{VectorXd::Zero(42)};
    x1(0) = 1;
    x1(3) = 1;
    x1(41) = 1;
    MatrixXd A1 = generate_Companion_Matrix(x1);

    int iter = 0;

    start = clock();
    iter = Schur_decomposition(A1);
    end = clock();

    std::cout << "the first task:" << std::endl;
    std::cout << "iter = " << iter << std::endl;
    std::cout << "time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "solution:" << std::endl;

    read_schur(A1);
    std::cout << std::endl;

    // example 2
    VectorXd x_list(3);
    x_list << 0.9, 1.0, 1.1;
    iter = 0;
    for (size_t i = 0; i < 3; i++)
    {
        MatrixXd A2(4, 4);
        A2 << 9.1, 3.0, 2.6, 4.0,
            4.2, 5.3, 4.7, 1.6,
            3.2, 1.7, 9.4, x_list(i),
            6.1, 4.9, 3.5, 6.2;

        iter = 0;

        start = clock();
        iter = Schur_decomposition(A2);
        end = clock();

        std::cout << "the second task:" << std::endl;
        std::cout << "x = " << x_list(i) << std::endl;
        std::cout << "iter = " << iter << std::endl;
        std::cout << "time = " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
        std::cout << "solution:" << std::endl;
        read_schur(A2);
        std::cout << std::endl;
    }
}

#endif
