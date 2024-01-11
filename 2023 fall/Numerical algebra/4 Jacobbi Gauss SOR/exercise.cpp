#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include "eigen-3.4.0/Eigen/Dense"
#include "function.h"
#include "function.cpp"

using namespace Eigen;

void exercise1()
{
    VectorXd aipu_list(4);
    aipu_list << 1, 0.1, 0.01, 0.0001;
    for (auto aipu : aipu_list)
    {
        std::cout << "--------------------------------------------------------";
        std::cout << "aipu =" << aipu << std::endl;
        test_jacobi(aipu);
        test_GS(aipu);
        test_SOR(aipu);
        std::cout << "--------------------------------------------------------";
        std::cout << std::endl
                  << std::endl;
    }
    std::cout << "--------------------------------------------------------";
    std::cout << "--------------------------------------------------------";
    std::cout << "--------------------------------------------------------";
    std::cout << "--------------------------------------------------------";
}

void exercise2()
{
    VectorXi N_list(3);
    N_list << 20, 40, 60;
    for (auto N : N_list)
    {
        std::cout << "--------------------------------------------------------";
        std::cout << "N =" << N << std::endl;
        test_jacobi(N);
        test_GS(N);
        test_SOR(N);
        std::cout << "--------------------------------------------------------";
        std::cout << std::endl
                  << std::endl;
    }
}