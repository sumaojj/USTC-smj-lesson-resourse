#pragma once
#include <iostream>
#include <vector>
using std::vector;

void forward_subs(vector<vector<double>> &L, vector<double> &b); // 前代法

void forward_subs1(vector<vector<double>> &L, vector<double> &b); // 对角元为1的前代法

void back_subs(vector<vector<double>> &U, vector<double> &b); // 回代法

void back_subs1(vector<vector<double>> &U, vector<double> &y); // 对角元为1的回代法

void gauss_elim(vector<vector<double>> &A); // Gauss消去法

void gauss_elim_full_pivoting(vector<vector<double>> &A, vector<int> &u, vector<int> &v); // 全主元Gauss消去法

void gauss_elim_col_pivoting(vector<vector<double>> &A, vector<int> &u); // 列主元Gauss消去法

void vector_pb(vector<int> &u, vector<double> &b); // 计算向量P*b【可选】

void vector_qb(vector<int> &v, vector<double> &b); // 计算向量Q*b【可选】

void cholesky_decomp(vector<vector<double>> &A); // 对称正定阵标准Cholesky分解

void modified_cholesky_decomp(vector<vector<double>> &A); // 改进的平方根法

void diag_solve(vector<vector<double>> &D, vector<double> &b); // solve Dx=b

// print vector
template <typename T3>
void print_vec(vector<T3> &b)
{
    int size = b.size();

    for (int i = 0; i < size; i++)
    {
        std::cout << b[i] << " ";
    }

    std::cout << "\n";
}
