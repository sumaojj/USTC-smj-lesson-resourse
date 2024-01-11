#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function1.1.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main()
{
    // initialize data for test
    // the problem is min c^T*x s.t. Ax=b,x>=0

    // the fist example
    /*MatrixXd A(3, 5); // constraint matrix size=m*n
    A << 2, 1, 1, 0, 0,
        1, 1, 0, 1, 0,
        0, 1, 0, 0, 1;
    VectorXd b(3); // constraint vector size=m*1
    b << 10, 8, 7;
    VectorXd c(5); // objective function  size=n*1
    c << -4, -3, 0, 0, 0;
    */

    // the second example
    /*MatrixXd A(3, 5); // constraint matrix size=m*n
    A << 1, 1, 1, 0, 0,
        2, -5, 1, -1, 0,
        1, 3, 1, 0, 1;
    VectorXd b(3); // constraint vector size=m*1
    b << 7, 10, 12;

    VectorXd c(5); // objective function  size=n*1
    c << -2, -3, 5, 0, 0;
    */

    // the third example
    // MatrixXd A(3, 10); // constraint matrix size=m*n
    // A << 4, 3, 2, 1, 1, 0, 0, -1, 0, 0,
    //     0, 1, 0, 2, 1, 3, 0, 0, -1, 0,
    //     0, 0, 1, 0, 1, 0, 2, 0, 0, -1;
    // VectorXd b(3); // constraint vector size=m*1
    // b << 50, 20, 15;
    // VectorXd c(10); // objective function  size=n*1
    // c << 3, 1, 3, 3, 1, 1, 3, 0, 0, 0;

    // PPt example 1 (solution found)
    // MatrixXd A(3, 6); // constraint matrix size=m*n
    // A << 1, 2, 2, 1, 0, 0,
    //     2, 1, 2, 0, 1, 0,
    //     2, 2, 1, 0, 0, 1;
    // VectorXd b(3); // constraint vector size=m*1
    // b << 20, 20, 20;
    // VectorXd c(6); // objective function  size=n*1
    // c << -10, -12, -12, 0, 0, 0;

    // PPt example 2 (have duplicate bounds)
    // MatrixXd A(3, 3); // constraint matrix size=m*n
    // A << 1, 2, 3,
    //     2, 4, 6,
    //     1, 1, 1;
    // VectorXd b(3); // constraint vector size=m*1
    // b << 6, 12, 3;
    // VectorXd c(3); // objective function  size=n*1
    // c << 1, 2, 3;

    // PPt example 3 (no feasible solution)
    // MatrixXd A(4, 3); // constraint matrix size=m*n
    // A << 1, 0, 0,
    //     0, 1, 0,
    //     0, 0, 1,
    //     1, 0, 1;
    // VectorXd b(4); // constraint vector size=m*1
    // b << 2, 2, 2, 2;
    // VectorXd c(3); // objective function  size=n*1
    // c << 1, 1, 1;

    // PPt example 4 (unbounded)
    MatrixXd A(2, 2); // constraint matrix size=m*n
    A << 1, -1,
        -1, 1;
    VectorXd b(2); // constraint vector size=m*1
    b << 0, 0;
    VectorXd c(2); // objective function  size=n*1
    c << -1, 0;

    linear_program_data p{A, b, c, 3};

    simplex_method(p);
    std::cout << "exitflag( 1 for solution found , -1 for unbounded, 0 for no feasible solution ) is:= " << p.exitflag << "\n";
    if (p.exitflag == 1)
    {
        std::cout << "optimal value is:= " << p.v << "\n";
        std::cout << "optimal solution is:= "
                  << "\n";
        for (int i = 0; i < p.n; i++)
        {
            std::cout << p.x_mini(i) << "\n";
        }
    }

    return 0;
}