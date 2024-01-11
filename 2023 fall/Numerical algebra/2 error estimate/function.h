#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "eigen-3.4.0/Eigen/Dense"
using namespace Eigen;

void forward_subs(MatrixXd &L, VectorXd &b)
{
    int num_row = L.rows(); // get size of metrix L

    // forward algorithm
    for (int i = 0; i < num_row - 1; i++)
    {
        b(i) = b(i) / L(i, i);
        for (int j = i + 1; j < num_row; j++)
        {
            b(j) = b(j) - b(i) * L(j, i);
        }
    }
    b(num_row - 1) /= L(num_row - 1, num_row - 1);
}

void forward_subs1(MatrixXd &L, VectorXd &b)
{
    int num_row = L.rows(); // get size of metrix L

    // forward algorithm dia 1
    for (int i = 0; i < num_row - 1; i++)
    {
        for (int j = i + 1; j < num_row; j++)
        {
            b(j) = b(j) - b(i) * L(j, i);
        }
    }
}

void back_subs(MatrixXd &U, VectorXd &y)
{
    int num_row = U.rows(); // get size of metrix U

    // backward algorithm
    for (int i = num_row - 1; i >= 1; i--)
    {
        y(i) = y(i) / U(i, i);
        for (int j = 0; j < i; j++)
        {
            y(j) = y(j) - y(i) * U(j, i);
        }
    }
    y[0] /= U(0, 0);
}

void back_subs1(MatrixXd &U, VectorXd &y)
{
    int num_row = U.rows(); // get size of metrix U

    // backward algorithm dia 1
    for (int i = num_row - 1; i >= 1; i--)
    {
        for (int j = 0; j < i; j++)
        {
            y(j) = y(j) - y(i) * U(j, i);
        }
    }
}

void gauss_elim(MatrixXd &A)
{
    int num_row = A.rows(); // get size of metrix A

    for (int k = 0; k < num_row - 1; k++)
    {

        /* for (int i = k+1; i < num_row; i++)
         {
             A(i,k)/=A(k,k);
         }
         */
        for (int i = k + 1; i < num_row; i++)
        {
            A(i, k) /= A(k, k);

            for (int j = k + 1; j < num_row; j++)
            {
                A(i, j) = A(i, j) - A(i, k) * A(k, j);
            }
        }
    }
}

void gauss_elim_col_pivoting(MatrixXd &A, VectorXi &u)
{
    int num_row = A.rows(); // get size of metrix A

    for (int k = 0; k < num_row - 1; k++)
    {
        int re_p{k}; // record biggest numbers' index

        for (int p = k; p < num_row; p++)
        {
            if (fabs(A(p, k)) > fabs(A(re_p, k)))
            {
                re_p = p;
            }
        }

        for (int j = 0; j < num_row; j++)
        {
            auto s{A(k, j)};
            A(k, j) = A(re_p, j);
            A(re_p, j) = s;
        }

        u(k) = re_p;

        if (A(k, k) != 0)
        {
            for (int i = k + 1; i < num_row; i++)
            {
                A(i, k) /= A(k, k);

                for (int j = k + 1; j < num_row; j++)
                {
                    A(i, j) = A(i, j) - A(i, k) * A(k, j);
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

void vector_pb(VectorXi &u, VectorXd &b)
{
    int num_row = u.rows(); // get size of vector u

    for (int i = 0; i < num_row; i++)
    {
        auto s{b(i)};
        b(i) = b(u(i));
        b(u(i)) = s;
    }
}

VectorXd solve_linear_equations(MatrixXd &A, VectorXd &b)
{
    int num_row = A.rows();
    MatrixXd A_1(num_row, num_row);
    VectorXd b_1(num_row); // copy otherwise change A b values
    A_1 = A;
    b_1 = b;

    VectorXi u = VectorXi::Zero(num_row - 1);

    gauss_elim_col_pivoting(A_1, u); // now  LU in A

    vector_pb(u, b_1); // now b_1=Pb

    forward_subs1(A_1, b_1); // now b_1=U*x

    back_subs(A_1, b_1); // now b_1=x

    return b_1;
}

MatrixXd generating_Hilbert_matrix(int n)
{
    MatrixXd H(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            H(i, j) = 1.0 / (i + j + 1);
        }
    }
    return H;
}

MatrixXd generating_special_matrix(int n)
{
    MatrixXd A = MatrixXd::Zero(n, n);

    for (int i = 0; i < n; i++)
    {
        A(i, i) = 1;
        A(i, n - 1) = 1;
        for (int j = 0; j < i; j++)
        {
            A(i, j) = -1;
        }
    }
    return A;
}

double compute_1_norm(MatrixXd &A)
{
    int num_col = A.cols();
    double norm = 0;
    for (int i = 0; i < num_col; i++)
    {

        if (A.colwise().lpNorm<1>().maxCoeff() > norm)
        {
            norm = A.colwise().lpNorm<1>().maxCoeff();
        }
    }
    return norm;
}

double compute_infty_norm(MatrixXd &A)
{
    int num_rows = A.rows();
    double norm = 0;
    for (int i = 0; i < num_rows; i++)
    {
        if (A.rowwise().lpNorm<1>().maxCoeff() > norm)
        {
            norm = A.rowwise().lpNorm<1>().maxCoeff();
        }
    }
    return norm;
}
void cholesky_decomp(MatrixXd &A)
{
    int num_row = A.rows(); // get size of metrix A

    for (int k = 0; k < num_row; k++)
    {
        A(k, k) = pow(A(k, k), 0.5);
        for (int j = k + 1; j < num_row; j++)
        {
            A(j, k) /= A(k, k);
        }
        for (int i = k + 1; i < num_row; i++)
        {
            for (int s = i; s < num_row; s++)
            {
                A(s, i) -= A(s, k) * A(i, k);
            }
        }
    }

    // storage L^T
    for (int i = 0; i < num_row; i++)
    {
        for (int j = i + 1; j < num_row; j++)
        {
            A(i, j) = A(j, i);
        }
    }
}
double compute_A_inverse_infty_norm(MatrixXd &A)
{
    int k = 1;
    int n = A.rows();
    double ret_v = 0;
    VectorXd x = VectorXd::Zero(n);
    for (int i = 0; i < n; i++)
    {
        x(i) = 1.0 / n;
    }
    MatrixXd A_transpose = A.transpose();
    while (k == 1)
    {
        VectorXd w = solve_linear_equations(A_transpose, x);

        VectorXd v(n);
        for (int i = 0; i < n; i++)
        {
            if (w(i) >= 0)
            {
                v(i) = 1;
            }
            else
                v(i) = -1;
        }

        VectorXd z = solve_linear_equations(A, v);

        if (z.lpNorm<Infinity>() <= z.dot(x))
        {
            k = 0;
            ret_v = w.lpNorm<1>();
        }
        else
        {
            double maxz = 0;
            int j = 0;
            for (int i = 0; i < n; i++)
            {
                if (fabs(z(i)) >= maxz)
                {
                    maxz = fabs(z(i));
                    j = i;
                }
            }

            x.setZero();
            x(j) = 1;
            k = 1;
        }
    }
    return ret_v;
}
