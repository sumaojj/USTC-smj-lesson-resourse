#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include "eigen-3.4.0/Eigen/Dense"
#include "function1.h"
using namespace Eigen;

clock_t start, end;

void exercise1_1()
{
    int N = 84; // size ofA
    MatrixXd A(N, N);
    A.setZero();
    VectorXd b(N);

    // initialize
    for (int i = 0; i < N - 1; i++)
    {
        A(i, i) = 6;
        A(i + 1, i) = 8;
        A(i, i + 1) = 1;
        b(i + 1) = 15;
    }
    A(N - 1, N - 1) = 6;
    b(0) = 7;
    b(N - 1) = 14;

    VectorXd x(N);
    start = clock();
    x = solve_linear_QR(A, b);
    end = clock();
    std::cout << "1.1 QR: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "time_QR = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";
    std::cout << "1.1 the error of QR is: " << (x - VectorXd::Ones(N)).transpose() << "\n\n"
              << std::endl;

    start = clock();
    x = solve_linear_equations(A, b);
    end = clock();
    std::cout << "1.1 PLU: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "time_PLU = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";
}

void exercise1_2()
{
    int N = 100; // size of A
    // initialize A b
    MatrixXd A{MatrixXd::Zero(N, N)};
    VectorXd b(N);
    for (int i = 0; i < N - 1; i++)
    {
        A(i, i) = 10;
        A(i + 1, i) = 1;
        A(i, i + 1) = 1;
    }
    A(N - 1, N - 1) = 10;

    b.setRandom();
    VectorXd x(N);
    start = clock();
    x = solve_linear_QR(A, b);
    end = clock();
    std::cout << "1.2 QR: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "time_QR = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";

    start = clock();
    x = solve_linear_equations(A, b);
    end = clock();
    std::cout << "1.2 PLU: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "time_PLU = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";
}

void exercise1_3()
{
    MatrixXd A(40, 40);
    A = generating_Hilbert_matrix(40);
    VectorXd b(40);
    for (int i = 0; i < 40; i++)
    {
        b(i) = 0;
        for (int j = 0; j < 40; j++)
        {
            b(i) += 1.0 / (i + j + 1);
        }
    }

    VectorXd x(40);
    start = clock();
    x = solve_linear_QR(A, b);
    end = clock();
    std::cout << "1.3 QR: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "time_QR = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";
    std::cout << "1.3 the error of QR is: " << (x - VectorXd::Ones(40)).transpose() << "\n\n";

    start = clock();
    x = solve_linear_equations(A, b);
    end = clock();
    std::cout << "1.3 PLU: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "time_PLU = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";

    std::cout << "1.3 the error of PLU is: " << (x - VectorXd::Ones(40)).transpose() << "\n\n";
}

void exercise1()
{
    exercise1_1();
    exercise1_2();
    exercise1_3();
    printline___1();
}

void exercise2()
{
    VectorXd t_0(7);
    t_0 = VectorXd::Ones(7);

    VectorXd t_1{{-1, -0.75, -0.5, 0, 0.25, 0.5, 0.75}};

    VectorXd t_2 = t_1.array().pow(2);
    VectorXd y{{1, 0.8125, 0.75, 1, 1.3125, 1.75, 2.3125}};
    MatrixXd A(7, 3);
    A << t_2, t_1, t_0;
    std::cout << "A = " << A << std::endl;
    VectorXd x(3);
    start = clock();
    x = solve_LS(A, y);
    end = clock();
    std::cout << "2 QR: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "2 squared-norm of error is: " << (A * x - y).squaredNorm() << std::endl;
    std::cout << "time_QR = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";
    printline___1();
}

void exercise3()
{
    MatrixXd A{{1, 4.9176, 1, 3.472, 0.998, 1, 7, 4, 42, 3, 1, 0},
               {1, 5.0208, 1, 3.531, 1.5, 2, 7, 4, 62, 1, 1, 0},
               {1, 4.5429, 1, 2.275, 1.175, 1, 6, 3, 40, 2, 1, 0},
               {1, 4.5573, 1, 4.05, 1.232, 1, 6, 3, 54, 4, 1, 0},
               {1, 5.0597, 1, 4.455, 1.121, 1, 6, 3, 42, 3, 1, 0},
               {1, 3.891, 1, 4.455, 0.988, 1, 6, 3, 56, 2, 1, 0},
               {1, 5.898, 1, 5.85, 1.24, 1, 7, 3, 51, 2, 1, 1},
               {1, 5.6039, 1, 9.52, 1.501, 0, 6, 3, 32, 1, 1, 0},
               {1, 15.4202, 2.5, 9.8, 3.42, 2, 10, 5, 42, 2, 1, 1},
               {1, 14.4598, 2.5, 12.8, 3, 2, 9, 5, 14, 4, 1, 1},
               {1, 5.8282, 1, 6.435, 1.225, 2, 6, 3, 32, 1, 1, 0},
               {1, 5.3003, 1, 4.9883, 1.552, 1, 6, 3, 30, 1, 2, 0},
               {1, 6.2712, 1, 5.52, 0.975, 1, 5, 2, 30, 1, 2, 0},
               {1, 5.9592, 1, 6.666, 1.121, 2, 6, 3, 32, 2, 1, 0},
               {1, 5.05, 1, 5, 1.02, 0, 5, 2, 46, 4, 1, 1},
               {1, 5.6039, 1, 9.52, 1.501, 0, 6, 3, 32, 1, 1, 0},
               {1, 8.2464, 1.5, 5.15, 1.664, 2, 8, 4, 50, 4, 1, 0},
               {1, 6.6969, 1.5, 6.092, 1.488, 1.5, 7, 3, 22, 1, 1, 1},
               {1, 7.7841, 1.5, 7.102, 1.376, 1, 6, 3, 17, 2, 1, 0},
               {1, 9.0384, 1, 7.8, 1.5, 1.5, 7, 3, 23, 3, 3, 0},
               {1, 5.9894, 1, 5.52, 1.256, 2, 6, 3, 40, 4, 1, 1},
               {1, 7.5422, 1.5, 4, 1.69, 1, 6, 3, 22, 1, 1, 0},
               {1, 8.7951, 1.5, 9.89, 1.82, 2, 8, 4, 50, 1, 1, 1},
               {1, 6.0931, 1.5, 6.7265, 1.652, 1, 6, 3, 44, 4, 1, 0},
               {1, 8.3607, 1.5, 9.15, 1.777, 2., 8, 4, 48, 1, 1, 1},
               {1, 8.14, 1, 8, 1.504, 2, 7, 3, 3, 1, 3, 0},
               {1, 9.1416, 1.5, 7.3262, 1.831, 1.5, 8, 4, 31, 4, 1, 0},
               {1, 12, 1.5, 5, 1.2, 2, 6, 3, 30, 3, 1, 1}};

    VectorXd y{{25.9, 29.5, 27.9, 25.9, 29.9, 29.9, 30.9,
                28.9, 84.9, 82.9, 35.9, 31.5, 31.0, 30.9,
                30.0, 28.9, 36.9, 41.9, 40.5, 43.9, 37.5,
                37.9, 44.5, 37.9, 38.9, 36.9, 45.8, 41.0}};

    VectorXd x(12);

    start = clock();
    x = solve_LS(A, y);
    end = clock();
    std::cout << "3 QR: Solution of Ax = b is: " << x.transpose() << std::endl;
    std::cout << "3 squared-norm of error is: " << (A * x - y).squaredNorm() << std::endl;
    std::cout << "time_QR = " << double(end - start) / CLOCKS_PER_SEC << "s"
              << "\n\n";
}