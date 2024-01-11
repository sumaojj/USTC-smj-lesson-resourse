#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "function.h"
#include "eigen-3.4.0/Eigen/Dense"

MatrixXd generate_jacobi_matrix(int n, int p, int q, double sin_theta, double cos_theta)
{
    MatrixXd J = MatrixXd::Identity(n, n);
    J(p, p) = J(q, q) = cos_theta;
    J(p, q) = sin_theta;
    J(q, p) = -sin_theta;
    return J;
}

MatrixXd generate_jacobi_matrix(int p, int q, MatrixXd &A)
{
    // this method will change A value
    int n = A.rows();
    if (A(p, q) == 0)
    {
        return MatrixXd::Identity(n, n);
    }
    double tau = (A(q, q) - A(p, p)) / (2 * A(p, q));
    double t;
    if (tau >= 0)
    {
        t = 1.0 / (tau + sqrt(1 + tau * tau));
    }
    else
    {
        t = -1.0 / (-tau + sqrt(1 + tau * tau));
    }

    double cos_theta = 1.0 / sqrt(1 + t * t);
    double sin_theta = t * cos_theta;

    for (int i = 0; i < n; i++)
    {
        if (i == p || i == q)
        {
            continue;
        }

        double temp = A(i, p);
        A(i, p) = cos_theta * temp - sin_theta * A(i, q);
        A(i, q) = sin_theta * temp + cos_theta * A(i, q);
        A(p, i) = A(i, p);
        A(q, i) = A(i, q);
    }

    double temp = A(p, p);
    A(p, p) = cos_theta * temp * cos_theta - 2 * sin_theta * cos_theta * A(p, q) + sin_theta * sin_theta * A(q, q);
    A(q, q) = sin_theta * sin_theta * temp + 2 * sin_theta * cos_theta * A(p, q) + cos_theta * cos_theta * A(q, q);
    A(p, q) = A(q, p) = 0;

    return generate_jacobi_matrix(n, p, q, sin_theta, cos_theta);
}

MatrixXd threshold_jacobi_3tr(MatrixXd &A, double threshold, int &iter)
{
    int n = A.rows();
    iter = 0;
    MatrixXd Q = MatrixXd::Identity(n, n);
    MatrixXd J = MatrixXd::Identity(n, n);
    bool threshold_low_enough = false;
    bool all_lower_thsh = true;

    while (!threshold_low_enough)
    {
        all_lower_thsh = true;
        for (int i = 0; i < n - 1; i++)
        {
            if (i == 0)
            {
                for (int j = 1; j < n; j++)
                {
                    if (abs(A(i, j)) > threshold)
                    {
                        J = generate_jacobi_matrix(i, j, A);
                        Q = Q * J;
                        iter++;
                        all_lower_thsh = false;
                    }
                }
            }

            for (int j = 0; j <= n && (j != i); j++)
            {
                if (abs(A(i, j)) > threshold)
                {
                    J = generate_jacobi_matrix(i, j, A);
                    Q = Q * J;
                    all_lower_thsh = false;
                    // std::cout << A << iter << std::endl;
                    iter++;
                }
            }
        }
        if (all_lower_thsh)
        {
            threshold = threshold / n;
        }
        if (threshold < 1e-11)
        {
            threshold_low_enough = true;
        }
    }

    return Q;
}

MatrixXd generate_special_matrix(int n)
{
    MatrixXd A = MatrixXd::Zero(n, n);
    for (int i = 0; i < n; i++)
    {
        A(i, i) = 4;
        if (i < n - 1)
        {
            A(i, i + 1) = 1;
            A(i + 1, i) = 1;
        }
    }
    return A;
}

int calculate_sign(double r, VectorXd &x, VectorXd &y)
{
    int n = x.size();
    int s = 0;
    double q = x(0) - r;
    for (int k = 0; k < n; k++)
    {
        if (q < 0)
        {
            s = s + 1;
        }
        if (k < n - 1)
        {
            if (q == 0)
            {
                q = 1e-15;
            }

            q = x(k + 1) - r - y(k + 1) * y(k + 1) / q;
        }
    }
    return s;
}

double bisection_3tri_method(MatrixXd &A, int m, int &iter)
{
    iter = 0;
    int n = A.rows();
    double edge = 2 * A.rowwise().lpNorm<1>().maxCoeff();
    // std::cout << edge << std::endl;
    double upper = edge;
    double lower = -edge;
    double mid = (upper + lower) / 2.0;

    double max_range = 1e-15;
    VectorXd x{VectorXd::Zero(n)};
    VectorXd y{VectorXd::Zero(n)};

    for (int i = 0; i < n; i++)
    {
        x(i) = A(i, i);
        if (i < n - 1)
        {
            y(i + 1) = A(i, i + 1);
        }
    }
    // std::cout << x.transpose() << std::endl;
    // std::cout << y.transpose() << std::endl;

    while (upper - lower > max_range)
    {
        if (calculate_sign(mid, x, y) >= m)
        {
            upper = mid;
        }
        else
        {
            lower = mid;
        }
        mid = (upper + lower) / 2.0;
        iter++;
    }
    return mid;
}

VectorXd inverse_power_method(MatrixXd &A, double lamda)
{
    int n = A.rows();
    VectorXd z{VectorXd::Ones(n)};

    MatrixXd B{A - lamda * MatrixXd::Identity(n, n)};

    z = B.partialPivLu().solve(z);
    return z / z.norm();
}

void read_diagonal(MatrixXd &A)
{
    // x(i) should be the i-th eigenvalue and in order from small to large
    int n = A.rows();
    VectorXd x{VectorXd::Zero(n)};
    for (int i = 0; i < n; i++)
    {
        x(i) = A(i, i);
    }
    std::sort(x.data(), x.data() + n);
    std::cout << "eigenvalues=" << std::endl;
    std::cout << x.transpose() << std::endl;
}
