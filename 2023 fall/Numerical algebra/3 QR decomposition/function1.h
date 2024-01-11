#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "eigen-3.4.0/Eigen/Dense"
#include "function.h"
using namespace Eigen;

void house_e1(VectorXd &x, VectorXd &v, double &s) // put reference!
{

    double nor = x.lpNorm<Infinity>();
    x = x / nor;
    double sigma = x(seq(1, last)).transpose() * x(seq(1, last));
    v(seq(1, last)) = x(seq(1, last));
    if (sigma == 0)
    {
        s = 0;
    }
    else
    {
        double alpha = pow(sigma + x(0) * x(0), 0.5);
        if (x(0) <= 0)
        {
            v(0) = x(0) - alpha;
        }
        else
            v(0) = -sigma / (x(0) + alpha);
    }
    s = 2 * v(0) * v(0) / (v(0) * v(0) + sigma);
    v = v / v(0);
}

void householderQR(MatrixXd &A, VectorXd &b, VectorXd &d)
{
    int m = A.rows();
    int n = A.cols();

    double s;
    for (int j = 0; j < n; j++)
    {
        if (j < m - 1)
        {
            VectorXd v(m - j);
            VectorXd A_j{A(seq(j, m - 1), j)};
            house_e1(A_j, v, s);

            // MatrixXd A_j_1{(MatrixXd::Identity(m - j, m - j) - s * v * v.transpose()) * A(seq(j, m - 1), seq(j, n - 1))};

            A(seq(j, m - 1), seq(j, n - 1)) = (MatrixXd::Identity(m - j, m - j) - s * v * v.transpose()) * A(seq(j, m - 1), seq(j, n - 1));
            VectorXd b_j{(MatrixXd::Identity(m - j, m - j) - s * v * v.transpose()) * b(seq(j, m - 1))};
            b(seq(j, m - 1)) = b_j;
            d(j) = s;
            A(seq(j + 1, m - 1), j) = v(seq(1, m - j - 1)); // why?
        }
    }
}

VectorXd solve_linear_QR(MatrixXd &A, VectorXd &b)
{
    MatrixXd A_copy = A;
    VectorXd b_copy = b; // do not change A,b

    int n = A.cols();
    VectorXd d(n);
    householderQR(A_copy, b_copy, d); //  now A storage R and vi, b=Hb

    back_subs(A_copy, b_copy);
    return b_copy;
}

VectorXd solve_LS(MatrixXd &A, VectorXd &b)
{

    int n = A.cols();
    VectorXd d(n);
    householderQR(A, b, d); //  now A storage R and vi, b=Hb
    VectorXd c1{b(seq(0, n - 1))};
    back_subs(A, c1);
    return c1;
}

void printline___1()
{
    std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------" << std::endl;
}
