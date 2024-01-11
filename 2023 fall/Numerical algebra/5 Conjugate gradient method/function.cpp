#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

MatrixXd generate_1_Matrix(int N)
{
    int n = N - 1;
    double h = 1.0 / N;
    MatrixXd A(n * n, n * n);
    A.setZero();
    MatrixXd S{MatrixXd::Zero(n, n)};
    for (int i = 0; i < n - 1; i++)
    {
        S(i, i) = 1 + 0.25 * h * h;
        S(i, i + 1) = -0.25;
        S(i + 1, i) = -0.25;
    }
    S(n - 1, n - 1) = 1 + 0.25 * h * h;

    for (int i = 0; i < n - 1; i++)
    {
        A(seqN(i * n, n), seqN(i * n, n)) = S;
        A(seqN(i * n, n), seqN((i + 1) * n, n)) = -0.25 * MatrixXd::Identity(n, n);
        A(seqN((i + 1) * n, n), seqN(i * n, n)) = -0.25 * MatrixXd::Identity(n, n);
    }
    A(seqN((n - 1) * n, n), seqN((n - 1) * n, n)) = S;
    return A;
}

VectorXd generate_1_Vector(int N)
{
    int n = N - 1;
    double h = 1.0 / N;
    VectorXd b(n * n);
    b.setZero();
    // first col
    b(0) = 0.5 * h * h + 0.25 * h * h * sin(h * h);
    for (int j = 1; j < n - 1; j++)
    {
        b(j) = 0.25 * (j + 1) * h * (j + 1) * h + 0.25 * h * h * sin(h * (j + 1) * h);
    }
    b(n - 1) = 0.25 * n * h * n * h + 0.25 * (h * h + 1) + 0.25 * h * h * sin(h * n * h);
    // second col to second last col
    for (int i = 1; i < n - 1; i++)
    {

        b(i * n) = 0.25 * (i + 1) * h * (i + 1) * h + 0.25 * h * h * sin((i + 1) * h * h);

        for (int j = 1; j < n - 1; j++)
        {
            b(i * n + j) = 0.25 * h * h * sin((i + 1) * h * (j + 1) * h);
        }
        b(i * n + n - 1) = 0.25 * ((i + 1) * h * (i + 1) * h + 1) + 0.25 * h * h * sin((i + 1) * h * n * h);
    }
    // last col
    b((n - 1) * n) = 0.25 * (h * h + 1) + 0.25 * n * h * n * h + 0.25 * h * h * sin(n * h * h);
    for (int j = 1; j < n - 1; j++)
    {
        b((n - 1) * n + j) = 0.25 * ((j + 1) * h * (j + 1) * h + 1) + 0.25 * h * h * sin(n * h * (j + 1) * h);
    }
    b((n - 1) * n + n - 1) = 0.5 * (n * h * n * h + 1) + 0.25 * h * h * sin(n * h * n * h);
    return b;
}

MatrixXd generate_Hilbert_MatrixXd(int n)
{
    MatrixXd A(n, n);
    A.setZero();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A(i, j) = 1.0 / double(i + j + 1);
        }
    }
    return A;
}

VectorXd generate_Hilbert_VectorXd(int n)
{
    VectorXd b(n);
    b.setZero();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b(i) += 1.0 / double(i + j + 1);
        }
    }
    return b;
}

VectorXd Jacobi_iteration_solve(MatrixXd &A, VectorXd &b, double epsilon, int &iter_num) // do not add ; here!
{
    int n = A.cols();
    iter_num = 0;
    VectorXd x(n);
    x.setOnes();
    MatrixXd B(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B(i, j) = -A(i, j) / A(i, i);
        }
        B(i, i) = 0;
    }
    // std::cout << B << std::endl;
    VectorXd g{b};
    for (int i = 0; i < n; i++)
    {
        g(i) = g(i) / A(i, i);
    }
    // std::cout << "Jacobi_iteration_solve: " << g.transpose() << std::endl;
    x = 1.0 / n * x;
    // std::cout << "Jacobi_iteration_solve: " << x.transpose() << std::endl;
    VectorXd x_pre{x};

    VectorXd r{b - A * x};
    while (r.lpNorm<Infinity>() > epsilon)
    {
        x = B * x + g;
        r = x - x_pre;
        x_pre = x;
        iter_num++;
    }
    // std::cout << "Jacobi_iteration_solve: " << x.transpose() << std::endl;
    return x;
}

VectorXd Gauss_Seidel_iteration_solve(MatrixXd &A, VectorXd &b, double epsilon, int &iter_num)
{
    int n = A.cols();
    VectorXd x(n);
    x.setOnes();
    MatrixXd B(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B(i, j) = -A(i, j) / A(i, i);
        }
        B(i, i) = 0;
    }

    VectorXd g{b};
    for (int i = 0; i < n; i++)
    {
        g(i) = g(i) / A(i, i);
    }

    x = 1.0 / n * x;
    VectorXd x_pre{x};

    VectorXd r{b - A * x};
    while (r.lpNorm<Infinity>() > epsilon)
    {
        for (int i = 0; i < n; i++)
        {
            x(i) = B(i, all) * x + g(i);
        }

        r = x - x_pre;
        x_pre = x;
        iter_num++;
    }

    return x;
}

VectorXd Conjugate_gradient_method(MatrixXd &A, VectorXd &b, VectorXd &x0, double epsilion, int &iter_num, int max_iter = 1000000000)
{
    VectorXd x{x0};
    VectorXd r{b - A * x};

    VectorXd p{r};
    double rou = r.transpose() * r;
    iter_num = 0;
    double alpha, beta, rou_old;
    while ((iter_num < max_iter) && (rou > epsilion))
    {
        iter_num++;
        if (iter_num == 1)
        {
            p = r;
        }
        else
        {
            beta = rou / rou_old;
            p = r + beta * p;
        }
        VectorXd w = A * p;
        alpha = rou / (p.transpose() * w);
        x = x + alpha * p;
        r = r - alpha * w;
        rou_old = rou;
        rou = r.transpose() * r;
    }

    return x;
}
