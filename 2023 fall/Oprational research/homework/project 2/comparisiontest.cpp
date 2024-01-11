#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function2.h"
#include "function2.1.h"

int main()
{
    VectorXi n_list(10);
    n_list << 2, 4, 6, 8, 10, 12, 14, 16, 18, 20;

    for (int i = 0; i < 10; i++)
    {
        VectorXi time_lp(20);
        VectorXi time_di(20);
        for (int j = 0; j < 20; j++)
        {
            MatrixXd G(n_list(i), n_list(i));
            initailize_Random_connected_graph(G, n_list(i)); // generate random adjacency matrix
            // std::cout << "G:" << std::endl;
            // std::cout << G << std::endl;
            VectorXd d(n_list(i));
            d = INF * VectorXd::Ones(n_list(i));
            d(0) = 0;
            int flag = checkifconnectedgraph(G); // 0==connected, 1==not connected ,-1==negative weight edge
            if (flag != 0)
            {
                i--;
                continue;
            }
            else
            {
                std::vector<int> P{};
                auto start = std::chrono::high_resolution_clock::now();
                for (int j = 0; j < n_list(i); j++)
                {
                    Fixed_Shortest_Circuit(d, P);
                    update(G, d, P);
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                time_di(j) = duration.count();

                linear_program_data data;
                VectorXd c(n_list(i) * n_list(i));
                for (int j = 0; j < n_list(i); j++)
                {

                    for (int k = 0; k < n_list(i); k++)
                    {
                        if (G(j, k) == INF)
                        {
                            c(j * n_list(i) + k) = 0;
                            continue;
                        }
                        c(j * n_list(i) + k) = G(j, k);
                    }
                }
                data.c = c;

                VectorXd b{VectorXd::Zero(n_list(i))};
                b(0) = 1;
                b(n_list(i) - 1) = -1;
                data.b = b;

                MatrixXd A{MatrixXd::Zero(n_list(i), n_list(i) * n_list(i))};
                for (int j = 0; j < n_list(i); j++)
                {
                    for (int k = 0; k < n_list(i); k++)
                    {
                        A(j, j * n_list(i) + k) = 1;
                        A(k, j * n_list(i) + k) = -1;
                    }
                }
                data.A = A;

                auto start1 = std::chrono::high_resolution_clock::now();
                simplex_method(data);
                auto end1 = std::chrono::high_resolution_clock::now();
                auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
                time_lp(j) = duration1.count();
            }
        }

        std::cout << "n=" << n_list(i) << std::endl;
        std::cout << "time_di:" << std::endl;
        double average_di = 0;
        for (int j = 0; j < 20; j++)
        {
            average_di += time_di(j);
        }
        average_di = average_di / 20;
        std::cout << average_di << std::endl;

        std::cout << "time_lp:" << std::endl;
        double average_lp = 0;
        for (int j = 0; j < 20; j++)
        {
            average_lp += time_lp(j);
        }
        average_lp = average_lp / 20;
        std::cout << average_lp << std::endl;
    }

    return 0;
}