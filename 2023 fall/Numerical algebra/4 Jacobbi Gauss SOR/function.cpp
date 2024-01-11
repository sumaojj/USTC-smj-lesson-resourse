#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "eigen-3.4.0/Eigen/Dense"
#include "function.h"

using namespace Eigen;

clock_t start, end;
int iter_num = 0;

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
    std::cout << "Jacobi_iteration_solve: " << x.transpose() << std::endl;
    return x;
}

MatrixXd Jacobi_iteration_solve(int N, double epsilon, int &iter_num) // do not add ; here!
{

    iter_num = 0;
    MatrixXd u(N + 1, N + 1);
    u.setOnes();
    double h = 1.0 / N;

    MatrixXd u_pre{u};
    MatrixXd r(N + 1, N + 1);
    do
    {

        for (int i = 1; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                u(i, j) = 1.0 / (4 + h * h * std::exp(i * h * j * h)) * (u_pre(i - 1, j) + u_pre(i, j - 1) + u_pre(i + 1, j) + u_pre(i, j + 1) + h * h * (i + j) * h);
            }
        }
        r = u - u_pre;
        u_pre = u;
        iter_num++;
    } while (r.cwiseAbs().colwise().sum().maxCoeff() > epsilon);

    return u;
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
MatrixXd Gauss_Seidel_iteration_solve(int N, double epsilon, int &iter_num) // do not add ; here!
{

    iter_num = 0;
    MatrixXd u(N + 1, N + 1);
    u.setOnes();
    double h = 1.0 / N;

    MatrixXd u_pre{u};
    MatrixXd r(N + 1, N + 1);
    do
    {

        for (int i = 1; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                u(i, j) = 1.0 / (4 + h * h * std::exp(i * h * j * h)) * (u(i - 1, j) + u(i, j - 1) + u_pre(i + 1, j) + u_pre(i, j + 1) + h * h * (i + j) * h);
            }
        }
        r = u - u_pre;
        u_pre = u;
        iter_num++;
    } while (r.cwiseAbs().colwise().sum().maxCoeff() > epsilon);

    return u;
}

VectorXd SOR_iteration_solve(MatrixXd &A, VectorXd &b, double epsilon, double w, int &iter_num)
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
    while ((r.lpNorm<Infinity>()) * w > epsilon)
    {
        for (int i = 0; i < n; i++)
        {
            x(i) = B(i, all) * x + g(i);
        }

        r = x - x_pre;
        x = x_pre + w * r;
        x_pre = x;
        iter_num++;
    }

    return x;
}
MatrixXd SOR_iteration_solve(int N, double epsilon, double w, int &iter_num) // do not add ; here!
{

    iter_num = 0;
    MatrixXd u(N + 1, N + 1);
    u.setOnes();
    double h = 1.0 / N;

    MatrixXd u_pre{u};
    MatrixXd r(N + 1, N + 1);
    do
    {

        for (int i = 1; i < N; i++)
        {
            for (int j = 1; j < N; j++)
            {
                u(i, j) = 1.0 / (4 + h * h * std::exp(i * h * j * h)) * (u(i - 1, j) + u(i, j - 1) + u_pre(i + 1, j) + u_pre(i, j + 1) + h * h * (i + j) * h);
            }
        }

        r = u - u_pre;
        u = u_pre + w * r;
        u_pre = u;
        iter_num++;
    } while (r.cwiseAbs().colwise().sum().maxCoeff() > epsilon);

    return u;
}

MatrixXd generate_matrix_1(double aipu)
{
    int n = 99;
    double h = 1.0 / (n + 1);
    MatrixXd A(n, n);
    A.setZero();
    for (int i = 0; i < n - 1; i++)
    {
        A(i, i) = -(2 * aipu + h);
        A(i + 1, i) = aipu;
        A(i, i + 1) = aipu + h;
    }
    A(n - 1, n - 1) = -(2 * aipu + h);
    return A;
}

VectorXd generate_vector_1(double aipu)
{
    int n = 99;
    double h = 1.0 / (n + 1);
    VectorXd b(n);
    b.setZero();
    for (int i = 0; i < n - 1; i++)
    {
        b(i) = 0.5 * h * h;
    }
    b(n - 1) = 0.5 * h * h - (aipu + h);
    return b;
}

VectorXd generate_accurate(double aipu)
{
    int n = 99;
    VectorXd b(n);
    double h = 1.0 / (n + 1);
    b.setZero();
    for (int i = 0; i < n; i++)
    {
        int j = i + 1;
        b(i) = 0.5 * (1.0 - std::exp(-j * h / aipu)) / (1.0 - std::exp(-1.0 / aipu)) + 0.5 * j * h;
    }

    return b;
}

void test_jacobi(double aipu)
{
    iter_num = 0;
    MatrixXd A{generate_matrix_1(aipu)};
    VectorXd b{generate_vector_1(aipu)};
    VectorXd x{generate_accurate(aipu)};

    // std::cout << A << std::endl;
    // std::cout << b << std::endl;
    // std::cout << x << std::endl;
    start = clock();
    VectorXd x_jacobi{Jacobi_iteration_solve(A, b, 1e-6, iter_num)};
    end = clock();

    VectorXd error = x_jacobi - x;
    std::cout << "jacobi: "
              << "\t\t time:" << double(end - start) / CLOCKS_PER_SEC << "\t\t iter_num:" << iter_num << "\t\t error:" << error.transpose() << std::endl;
}

void test_GS(double aipu)
{
    iter_num = 0;
    MatrixXd A{generate_matrix_1(aipu)};
    VectorXd b{generate_vector_1(aipu)};
    VectorXd x{generate_accurate(aipu)};

    // std::cout << A << std::endl;
    // std::cout << b << std::endl;
    // std::cout << x << std::endl;
    start = clock();
    VectorXd x_jacobi{Gauss_Seidel_iteration_solve(A, b, 1e-6, iter_num)};
    end = clock();

    VectorXd error = x_jacobi - x;
    std::cout << "GS: "
              << "\t\t time:" << double(end - start) / CLOCKS_PER_SEC << "\t\t iter_num:" << iter_num << "\t\t error:" << error.transpose() << std::endl;
}

void test_SOR(double aipu)
{
    iter_num = 0;
    MatrixXd A{generate_matrix_1(aipu)};
    VectorXd b{generate_vector_1(aipu)};
    VectorXd x{generate_accurate(aipu)};

    // std::cout << A << std::endl;
    // std::cout << b << std::endl;
    // std::cout << x << std::endl;
    start = clock();
    VectorXd x_jacobi{SOR_iteration_solve(A, b, 1e-6, 1.2, iter_num)};
    end = clock();

    VectorXd error = x_jacobi - x;
    std::cout << "SOR: "
              << "\t\t time:" << double(end - start) / CLOCKS_PER_SEC << "\t\t iter_num:" << iter_num << "\t\t error:" << error.transpose() << std::endl;
}

void test_jacobi(int N)
{
    iter_num = 0;

    start = clock();
    MatrixXd x_jacobi{Jacobi_iteration_solve(N, 1e-7, iter_num)};
    end = clock();

    std::cout << "jacobi: "
              << "\t\t time:" << double(end - start) / CLOCKS_PER_SEC << "\t\t iter_num:" << iter_num << "\t\t mini:" << x_jacobi.minCoeff() << std::endl;
}

void test_GS(int N)
{
    iter_num = 0;

    start = clock();
    MatrixXd x_gs{Gauss_Seidel_iteration_solve(N, 1e-7, iter_num)};
    end = clock();

    std::cout << "Gauss_Seidel: "
              << "\t\t time:" << double(end - start) / CLOCKS_PER_SEC << "\t\t iter_num:" << iter_num << "\t\t mini:" << x_gs.minCoeff() << std::endl;
}

void test_SOR(int N)
{
    iter_num = 0;

    start = clock();
    MatrixXd x_sor{SOR_iteration_solve(N, 1e-7, 1.55, iter_num)};
    end = clock();

    std::cout << "SOR: "
              << "\t\t time:" << double(end - start) / CLOCKS_PER_SEC << "\t\t iter_num:" << iter_num << "\t\t mini:" << x_sor.minCoeff() << "\t\tw=" << 1.55 << std::endl;
}
