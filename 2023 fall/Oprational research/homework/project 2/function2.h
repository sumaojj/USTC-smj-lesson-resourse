#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;
const int INF = std::numeric_limits<int>::max();

// generate adjacency matrix
void initailize_Random_connected_graph(MatrixXd &G, int n)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < n - 1; i++)
    {
        G(i, i) = 0;
        for (int j = i + 1; j < n; j++)
        {
            G(i, j) = rand() % 100;
            G(j, i) = G(i, j);
        }
    }
    G(n - 1, n - 1) = 0;
}

bool Isadjacent(int u, int v, MatrixXd &G)
{
    if (G(u, v) != INF)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// check if there is a edge between u and v
void traverse(int u, VectorXi &visited, MatrixXd &G)
{
    int n = G.rows();
    visited(u) = 1;
    for (int i = 0; i < n; i++)
    {
        if (Isadjacent(u, i, G) && visited(i) == 0)
        {
            visited(i) = 1;
            traverse(i, visited, G);
        }
    }
}

int checkifconnectedgraph(MatrixXd &G) // 0==connected, 1==not connected ,-1==negative weight edge
{
    int n = G.rows();
    for (int i = 0; i < n; i++)
    {
        // check if there is negative weight edge
        for (int j = 0; j < n; j++)
        {
            if ((G(i, j) < 0) && (G(i, j) != INF))
            {
                return -1;
            }
        }
    }

    // check diagonal
    for (int i = 0; i < n; i++)
    {
        if (G(i, i) != 0)
        {
            return 1;
        }
    }

    // check if connected
    VectorXi visited(n);
    visited = VectorXi::Zero(n);
    traverse(0, visited, G);
    for (int i = 0; i < n; i++)
    {
        if (visited(i) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void Fixed_Shortest_Circuit(VectorXd &d, std::vector<int> &P)
{
    int n = d.rows();
    std::sort(P.begin(), P.end());
    std::vector<int> Q{}; // index vector
    std::vector<int> I{}; // all indexs
    for (int k = 0; k < n; k++)
    {
        I.push_back(k);
    }

    std::set_difference(I.begin(), I.end(), P.begin(), P.end(), std::back_inserter(Q)); // can use method in project1.1 instead

    int i_0 = Q[0]; // get address of min in d
    for (int i : Q)
    {
        if (d(i) < d(i_0))
        {
            i_0 = i;
        }
    }

    P.push_back(i_0);
}

void update(MatrixXd &G, VectorXd &d, std::vector<int> &P)
{
    int n = d.rows();
    std::sort(P.begin(), P.end());
    std::vector<int> Q{}; // index vector
    std::vector<int> I{}; // all indexs
    for (int k = 0; k < n; k++)
    {
        I.push_back(k);
    }

    std::set_difference(I.begin(), I.end(), P.begin(), P.end(), std::back_inserter(Q)); // can use method in project1.1 instead

    for (int j : P)
    {
        for (int i : Q)
        {
            d(i) = std::min(d(i), d(j) + G(j, i));
        }
    }
}