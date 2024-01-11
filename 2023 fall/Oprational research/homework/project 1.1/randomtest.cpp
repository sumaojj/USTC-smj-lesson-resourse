#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function1.1.h"

clock_t start, end;

int main()
{
    // generate 20 n lists for n*n matrix A with random numbers and n*1 vector b with random numbers
    std::vector<int> n_list{5, 10, 15, 20, 30};

    // generate time matrix to restore time

    MatrixXd time(20, 7);
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 20; i++)
        {
            int n = n_list[j];
            MatrixXd A = MatrixXd::Random(n, n);
            VectorXd b = VectorXd::Random(n);
            VectorXd c = VectorXd::Random(n);
            std::srand((unsigned)std::time(nullptr));
            linear_program_data p{A, b, c, n};
            start = clock();
            simplex_method(p);
            end = clock();
            if (p.exitflag == 1)
            {
                std::cout << "n=" << n << " solution found" << std::endl;
                std::cout << "time is " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
                time(i, j) = (double)(end - start) / CLOCKS_PER_SEC;
            }
            else
                i--;
        }
    }

    // initialize time matrix for n=40, 50
    time.col(5) << 1.62, 0.488, 2.695, 2.837, 0.297, 0.703, 0.707, 10.936, 11.268, 12.116, 0.757, 1.789, 3.226, 0.376, 0.741, 0.736, 0.309, 0.555, 0.571, 1.023;
    time.col(6) << 7.739, 7.403, 7.44, 7.410, 7.619, 7.671, 9.868, 7.33, 7.367, 7.68, 7.794, 3.86, 8.482, 14.682, 29.088, 8.123, 7.692, 3.275, 2.201, 7.401;

    // calculate average time and standard deviation for each n and restore in two vectors
    VectorXd average_time(7);
    VectorXd standard_deviation(7);
    for (int i = 0; i < 7; i++)
    {
        average_time(i) = time.col(i).mean();
        standard_deviation(i) = std::sqrt((time.col(i).array() - average_time(i)).square().sum() / 20);
    }
    std::cout << "average time is (s) " << std::endl
              << average_time << std::endl;
    std::cout << "standard deviation is (s)" << std::endl
              << standard_deviation << std::endl;

    return 0;
}