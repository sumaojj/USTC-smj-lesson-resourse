#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
#include "function2.h"

using namespace Eigen;

int main()
{
    MatrixXd G;
    // initailize_Random_connected_graph(G); // generate random adjacency matrix
    // G==n*n adjacency matrix

    // first example connected graph1
    // G.resize(4, 4);
    // G << 0, 1, 2, 3,
    //     1, 0, 4, 5,
    //     2, 4, 0, 6,
    //     3, 5, 6, 0;

    // second example negative weight edge
    // G.resize(4, 4);
    // G << 0, 1, 2, 3,
    //     1, 0, 4, 5,
    //     2, 4, 0, -6,
    //     3, 5, -6, 0;

    // third example not connected
    // G.resize(4, 4);
    // G << 0, 1, INF, INF,
    //     1, 0, INF, INF,
    //     INF, INF, 0, 6,
    //     INF, INF, 6, 0;

    // fourth example  connected2
    // G.resize(4, 4);
    // G << 0, 1, 4, 6,
    //     INF, 0, INF, 2,
    //     INF, INF, 0, 1,
    //     INF, INF, INF, 0;

    // fifth example connected3 (home work example)
    G.resize(5, 5);
    G << 0, 4000, 5400, 9800, INF,
        INF, 0, 4300, 6200, 8700,
        INF, INF, 0, 4800, 7100,
        INF, INF, INF, 0, 4900,
        INF, INF, INF, INF, 0;

    int flag = checkifconnectedgraph(G); // 0==connected, 1==not connected ,-1==negative weight edge
    if (flag == -1)
    {
        std::cout << "There is negative weight edge in the graph." << std::endl;
        return 0;
    }
    else if (flag == 1)
    {
        std::cout << "The graph is not connected." << std::endl;
        return 0;
    }

    int n = G.rows();

    // initialize d
    VectorXd d(n);
    d = INF * VectorXd::Ones(n);
    d(0) = 0;

    std::vector<int> P{};

    for (int i = 0; i < n; i++)
    {
        Fixed_Shortest_Circuit(d, P);
        update(G, d, P);
    }

    std::cout << "Shortest circuit: \n"
              << d << std::endl;
}