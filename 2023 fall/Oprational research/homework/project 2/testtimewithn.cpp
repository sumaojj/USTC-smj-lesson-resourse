#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function2.h"
// #include "C:\Users\26557\copt\copt70\include\coptcpp_inc\coptcpp_pch.h"
// #include "coptcpp_pch.h"
// generate relative path to C:\Users\26557\copt\copt70\include\coptcpp_inc\coptcpp_pch.h with D:\STudy\the first semester of junior\Oprational research\homework\project 2

using namespace Eigen;
clock_t start, end;

int main()
{
    VectorXi n_list(20);
    n_list << 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
        200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000;

    VectorXd time_list_di(20);

    for (int i = 0; i < 20; i++)
    {
        MatrixXd G(n_list(i), n_list(i));
        initailize_Random_connected_graph(G, n_list(i)); // generate random adjacency matrix

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
            start = clock();
            for (int j = 0; j < n_list(i); j++)
            {
                Fixed_Shortest_Circuit(d, P);
                update(G, d, P);
            }
            end = clock();
            time_list_di(i) = (double)(end - start) / CLOCKS_PER_SEC;
        }

        // std::cout << "n:" << std::endl;
        // std::cout << n_list(i) << std::endl;
        // std::cout << "d:" << std::endl;
        // std::cout << d.transpose() << std::endl;
    }

    std::cout << "time_list_di:" << std::endl;
    std::cout << time_list_di << std::endl;
    return 0;
}