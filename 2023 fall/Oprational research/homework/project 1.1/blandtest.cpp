#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function1.1.h"

void Axis_operation_b(linear_program_data &p)
{
    int m = p.A.rows();
    int n = p.A.cols();

    MatrixXd B = p.A(all, p.index);
    VectorXd y_e = B.inverse() * p.A.col(p.e);
    VectorXd x_B = B.inverse() * p.b;

    // std::cout << y_e << std::endl;
    for (int i = 0; i < m; i++)
    {
        if (y_e(i) > 0)
        {
            break;
        }
        if (i == m - 1)
        {
            p.exitflag = -1; // unbounded
            return;
        }
    }

    int r = 0; // record min r
    bool first = true;
    for (int i = 0; i < m; i++)
    {
        if (y_e(i) > 0 && first == true)
        {
            r = i;
            first = false;
            continue;
        }
        if (y_e(i) > 0)
        {

            if ((x_B(i) / y_e(i)) < (x_B(r) / y_e(r)))
            {
                r = i;
            }
        }
    }
    p.index(r) = p.e;
}

bool optimal_decision_b(linear_program_data &p)
{
    int m = p.A.rows();
    int n = p.A.cols();

    VectorXi tempindex = VectorXi::Zero(n);
    for (int i = 0; i < m; i++)
    {
        tempindex(p.index(i)) = 1;
    }

    MatrixXd B = p.A(all, p.index);

    VectorXd c_B = p.c(p.index);
    MatrixXd B_t{B.transpose()};

    VectorXd w{B_t.inverse() * c_B};

    p.v = w.dot(p.b);

    p.x_mini(p.index) = B.inverse() * p.b; // have to get proper order using index

    // std::cout << w << std::endl;

    double z;

    for (int i = 0; i < n; i++)
    {
        if (tempindex(i) == 0) // i is  in index of N
        {
            z = w.dot(p.A.col(i));
            // indexN(j) = i;

            if (z > p.c(i))
            {
                p.e = i;
                // std::cout << p.e << std::endl;
                return false;
            }
        }
    }

    return true;
}

int main()
{
    // test bland's rule
    MatrixXd A(3, 7); // constraint matrix size=m*n
    A << 0.25, -8, -1, 9, 1, 0, 0,
        0.5, -12, -0.5, 3, 0, 1, 0,
        0, 0, 1, 0, 0, 0, 1;
    VectorXd b(3); // constraint vector size=m*1
    b << 0, 0, 1;
    VectorXd c(7); // objective function  size=n*1
    c << -0.75, 20, -0.5, 6, 0, 0, 0;

    linear_program_data p{A, b, c, 7};

    p.x_mini = VectorXd::Zero(7);

    p.index = VectorXi::Ones(3);
    p.index(0) = 4;
    p.index(1) = 5;
    p.index(2) = 6;

    while (optimal_decision_b(p) == false && p.exitflag != -1)
    {
        std::cout << p.index.transpose() << std::endl;

        Axis_operation_b(p);
    }

    std::cout << "out of while loop" << std::endl;

    return 0;
}