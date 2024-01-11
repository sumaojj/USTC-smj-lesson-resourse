#include "Function.h"
#include <cmath>
#include <algorithm>
using std::vector;

void forward_subs(vector<vector<double>> &L, vector<double> &b)
{
    int num_row = L.size(); // get size of metrix L

    // forward algorithm
    for (int i = 0; i < num_row - 1; i++)
    {
        b[i] = b[i] / L[i][i];
        for (int j = i + 1; j < num_row; j++)
        {
            b[j] = b[j] - b[i] * L[j][i];
        }
    }
    b[num_row - 1] /= L[num_row - 1][num_row - 1];
}

void forward_subs1(vector<vector<double>> &L, vector<double> &b)
{
    int num_row = L.size(); // get size of metrix L

    // forward algorithm dia 1
    for (int i = 0; i < num_row - 1; i++)
    {
        for (int j = i + 1; j < num_row; j++)
        {
            b[j] = b[j] - b[i] * L[j][i];
        }
    }
}

void back_subs(vector<vector<double>> &U, vector<double> &y)
{
    int num_row = U.size(); // get size of metrix U

    // backward algorithm
    for (int i = num_row - 1; i >= 1; i--)
    {
        y[i] = y[i] / U[i][i];
        for (int j = 0; j < i; j++)
        {
            y[j] = y[j] - y[i] * U[j][i];
        }
    }
    y[0] /= U[0][0];
}

void back_subs1(vector<vector<double>> &U, vector<double> &y)
{
    int num_row = U.size(); // get size of metrix U

    // backward algorithm dia 1
    for (int i = num_row - 1; i >= 1; i--)
    {
        for (int j = 0; j < i; j++)
        {
            y[j] = y[j] - y[i] * U[j][i];
        }
    }
}

void gauss_elim(vector<vector<double>> &A)
{
    int num_row = A.size(); // get size of metrix A

    for (int k = 0; k < num_row - 1; k++)
    {

        /* for (int i = k+1; i < num_row; i++)
         {
             A[i][k]/=A[k][k];
         }
         */
        for (int i = k + 1; i < num_row; i++)
        {
            A[i][k] /= A[k][k];

            for (int j = k + 1; j < num_row; j++)
            {
                A[i][j] = A[i][j] - A[i][k] * A[k][j];
            }
        }
    }
}

void gauss_elim_full_pivoting(vector<vector<double>> &A, vector<int> &u, vector<int> &v)
{
    int num_row = A.size(); // get size of metrix A

    for (int k = 0; k < num_row - 1; k++)
    {
        int re_p{k};
        int re_q{k}; // record biggest numbers' index

        for (int p = k; p < num_row; p++)
        {

            for (int q = k; q < num_row; q++)
            {
                if (fabs(A[p][q]) > fabs(A[re_p][re_q]))
                {
                    re_p = p;
                    re_q = q;
                }
            }
        }

        u[k] = re_p;
        v[k] = re_q;

        for (int j = 0; j < num_row; j++)
        {
            auto s{A[k][j]};
            A[k][j] = A[re_p][j];
            A[re_p][j] = s;
        }

        for (int j = 0; j < num_row; j++)
        {
            auto s{A[j][k]};
            A[j][k] = A[j][re_q];
            A[j][re_q] = s;
        }

        if (A[k][k] != 0)
        {
            for (int i = k + 1; i < num_row; i++)
            {
                A[i][k] /= A[k][k];

                for (int j = k + 1; j < num_row; j++)
                {
                    A[i][j] = A[i][j] - A[i][k] * A[k][j];
                }
            }
        }
        else
        {
            std::cout << "input matrix is an singular matrix"
                      << "\n";
            break;
        }
    }
}

void gauss_elim_col_pivoting(vector<vector<double>> &A, vector<int> &u)
{
    int num_row = A.size(); // get size of metrix A

    for (int k = 0; k < num_row - 1; k++)
    {
        int re_p{k}; // record biggest numbers' index

        for (int p = k; p < num_row; p++)
        {
            if (fabs(A[p][k]) > fabs(A[re_p][k]))
            {
                re_p = p;
            }
        }

        for (int j = 0; j < num_row; j++)
        {
            auto s{A[k][j]};
            A[k][j] = A[re_p][j];
            A[re_p][j] = s;
        }

        u[k] = re_p;

        if (A[k][k] != 0)
        {
            for (int i = k + 1; i < num_row; i++)
            {
                A[i][k] /= A[k][k];

                for (int j = k + 1; j < num_row; j++)
                {
                    A[i][j] = A[i][j] - A[i][k] * A[k][j];
                }
            }
        }
        else
        {
            std::cout << "input matrix is an singular matrix";
            break;
        }
    }
}

void vector_pb(vector<int> &u, vector<double> &b)
{
    int num_row = u.size(); // get size of vector u

    for (int i = 0; i < num_row; i++)
    {
        auto s{b[i]};
        b[i] = b[u[i]];
        b[u[i]] = s;
    }
}

void vector_qb(vector<int> &v, vector<double> &b)
{
    int num_row = v.size(); // get size of vector v

    for (int i = num_row - 1; i >= 0; i--)
    {
        auto s{b[i]};
        b[i] = b[v[i]];
        b[v[i]] = s;
    }
}

void cholesky_decomp(vector<vector<double>> &A)
{
    int num_row = A.size(); // get size of metrix A

    for (int k = 0; k < num_row; k++)
    {
        A[k][k] = pow(A[k][k], 0.5);
        for (int j = k + 1; j < num_row; j++)
        {
            A[j][k] /= A[k][k];
        }
        for (int i = k + 1; i < num_row; i++)
        {
            for (int s = i; s < num_row; s++)
            {
                A[s][i] -= A[s][k] * A[i][k];
            }
        }
    }

    // storage L^T
    for (int i = 0; i < num_row; i++)
    {
        for (int j = i + 1; j < num_row; j++)
        {
            A[i][j] = A[j][i];
        }
    }
}

void modified_cholesky_decomp(vector<vector<double>> &A)
{
    int num_row = A.size(); // get size of metrix A
    vector<double> v(num_row);

    for (int j = 0; j < num_row; j++)
    {
        for (int i = 0; i < j - 1; i++)
        {
            v[i] = A[j][i] * A[i][i];
        }

        for (int i = 0; i < j; i++)
        {
            A[j][j] -= A[j][i] * v[i];
        }
        for (int i = j + 1; i < num_row; i++)
        {
            for (int k = 0; k < j; k++)
            {
                A[i][j] = (A[i][j] - A[i][k] * v[k]) / A[j][j];
            }
        }
    }

    // storage L^T
    for (int i = 0; i < num_row; i++)
    {
        for (int j = i + 1; j < num_row; j++)
        {
            A[i][j] = A[j][i];
        }
    }
}

void diag_solve(vector<vector<double>> &D, vector<double> &b)
{
    int num_row = D.size(); // get size of metrix D

    for (int i = 0; i < num_row; i++)
    {
        b[i] /= D[i][i];
    }
}
