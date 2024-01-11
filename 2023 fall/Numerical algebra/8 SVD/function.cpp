#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "exercise.h"
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

MatrixXd generate_jacobi_matrix(int n, int p, int q, double sin_theta, double cos_theta)
{
    MatrixXd J = MatrixXd::Identity(n, n);
    J(p, p) = J(q, q) = cos_theta;
    J(p, q) = sin_theta;
    J(q, p) = -sin_theta;
    return J;
}

void house_e1(VectorXd &x, VectorXd &v, double &beta) // put reference!
{
    // std::cout << "x = " << x.transpose() << std::endl;

    double nor = x.lpNorm<Infinity>();
    if (nor == 0)
    {
        beta = 0;
        return;
    }
    x = x / nor;
    double sigma = x(seq(1, last)).transpose() * x(seq(1, last));
    v(seq(1, last)) = x(seq(1, last));
    if (sigma == 0)
    {
        beta = 0;
        return;
    }
    else
    {
        double alpha = pow(sigma + x(0) * x(0), 0.5);
        if (x(0) <= 0)
        {
            v(0) = x(0) - alpha;
        }
        else
            v(0) = -sigma / (x(0) + alpha);
    }
    // std::cout << "v = " << v.transpose() << std::endl;
    beta = 2 * v(0) * v(0) / (v(0) * v(0) + sigma);
    v = v / v(0);
}

void Didiagonalization(MatrixXd &A, MatrixXd &U, MatrixXd &V)
{
    // b.size=n, c.size=n-2
    //  defalut: A is m*n matrix, m>=n
    int m = A.rows();
    int n = A.cols();
    MatrixXd U_tr{MatrixXd::Identity(m, m)};

    for (int k = 0; k < n; k++)
    {
        VectorXd x{A(seq(k, last), k)};
        VectorXd v{VectorXd::Zero(m - k)};
        double beta;
        house_e1(x, v, beta);
        A(seq(k, m - 1), seq(k, n - 1)) = (MatrixXd::Identity(m - k, m - k) - beta * v * v.transpose()) * A(seq(k, m - 1), seq(k, n - 1));
        U(all, seq(k, m - 1)) = U(all, seq(k, m - 1)) * (MatrixXd::Identity(m - k, m - k) - beta * v * v.transpose());

        if (k < n - 2)
        {
            VectorXd x{A(k, seq(k + 1, n - 1)).transpose()};
            VectorXd v{VectorXd::Zero(n - k - 1)};
            double beta;
            house_e1(x, v, beta);
            A(seq(k, last), seq(k + 1, last)) = A(seq(k, last), seq(k + 1, last)) * (MatrixXd::Identity(n - k - 1, n - k - 1) - beta * v * v.transpose());
            V(all, seq(k + 1, n - 1)) = V(all, seq(k + 1, n - 1)) * (MatrixXd::Identity(n - k - 1, n - k - 1) - beta * v * v.transpose());
        }
    }
}

void shift_QR_sym(VectorXd &sig, VectorXd &gamma, MatrixXd &Q, MatrixXd &P)
{

    double mu;
    int n = sig.size();
    if (n == 2)
    {
        mu = sig(1);
    }
    else
    {
        double alpha = sig(n - 1) * sig(n - 1) + gamma(n - 2) * gamma(n - 2);
        double beta = sig(n - 2) * gamma(n - 2);
        double sigma = (sig(n - 2) * sig(n - 2) + gamma(n - 3) * gamma(n - 3) - alpha) / 2;

        if (sigma >= 0)
        {
            mu = alpha - beta * beta / (sigma + std::pow(sigma * sigma + beta * beta, 0.5));
        }
        else
            mu = alpha - beta * beta / (sigma - std::pow(sigma * sigma + beta * beta, 0.5));
    }

    double y = sig(0) * sig(0) - mu;
    double z = sig(0) * gamma(0);

    double c;
    double s;

    // MatrixXd Q = MatrixXd::Identity(n, n);
    // MatrixXd P = MatrixXd::Identity(n, n);

    for (int k = 0; k < n - 1; k++)
    {
        if (k != 0)
        {
            // update Q and s,c
            s = -z / std::pow(y * y + z * z, 0.5);
            c = y / std::pow(y * y + z * z, 0.5);
            gamma(k - 1) = c * y - s * z;
        }
        else
        {
            // update Q and s,c
            s = -z / std::pow(y * y + z * z, 0.5);
            c = y / std::pow(y * y + z * z, 0.5);
        }

        // update Q and y,z
        Q = Q * generate_jacobi_matrix(n, k, k + 1, s, c);
        y = c * sig(k) - s * gamma(k);
        z = -s * sig(k + 1);

        // update sig and gamma
        gamma(k) = s * sig(k) + c * gamma(k);
        sig(k) = y;
        sig(k + 1) = c * sig(k + 1);

        // update P and s,c
        s = -z / std::pow(y * y + z * z, 0.5);
        c = y / std::pow(y * y + z * z, 0.5);
        P = P * generate_jacobi_matrix(n, k, k + 1, s, c);
        sig(k) = c * y - s * z;

        if (k < n - 2)
        {
            // update  y,z
            y = c * gamma(k) - s * sig(k + 1);
            z = -s * gamma(k + 1);

            // update sig and gamma
            sig(k + 1) = s * gamma(k) + c * sig(k + 1);
            gamma(k) = y;
            gamma(k + 1) = c * gamma(k + 1);
        }
        else
        {
            double temp = c * gamma(k) - s * sig(k + 1);
            sig(k + 1) = s * gamma(k) + c * sig(k + 1);
            gamma(k) = temp;
        }
    }
}

void SVD_method(MatrixXd &A, int &iter, MatrixXd &U, MatrixXd &V, VectorXd &singular)
{
    iter = 0;
    int m = A.rows();
    int n = A.cols();
    VectorXd b{VectorXd::Zero(n)};
    VectorXd c{VectorXd::Zero(n - 2)};

    MatrixXd A_0{A};
    Didiagonalization(A, U, V);
    // std::cout << "A = " << A << std::endl;
    // std::cout << U * A * V.transpose() - A_0 << std::endl;

    VectorXd sig{A.diagonal()};
    VectorXd gamma{A(all, seq(1, n - 1)).diagonal()};
    // std::cout << "sig = " << sig.transpose() << std::endl;
    // std::cout << "gamma = " << gamma.transpose() << std::endl;
    //  std::cout << "A = " << A << std::endl;
    //  std::cout << U * A * V.transpose() - A_0 << std::endl;

    int k = -1;

    while (true)
    {
        // std::cout << "sig = " << sig.transpose() << std::endl;
        // std::cout << "gamma = " << gamma.transpose() << std::endl;

        double p = 0;
        double q = n;

        for (int i = 0; i < n; i++)
        {
            if (std::fabs(sig(i)) < 1e-10)
            {
                sig(i) = 0;
            }
        }

        for (int i = 0; i < n - 1; i++)
        {
            if (std::fabs(gamma(i)) < 1e-10)
            {
                gamma(i) = 0;
            }
        }

        for (int i = n - 2; i >= 0; i--)
        {
            if (gamma(i) != 0)
            {
                q = n - i - 2;
                break;
            }
        }

        for (int i = 0; i < n - 1; i++)
        {
            if (gamma(i) != 0)
            {
                p = i;
                break;
            }
        }

        if (q == n)
        {
            break;
        }

        for (int i = p; i < n - q; i++)
        {
            if (sig(i) == 0)
            {
                k = i;
                break;
            }
        }

        if (k < 0)
        {
            MatrixXd Q = MatrixXd::Identity(n - p - q, n - p - q);
            MatrixXd P = MatrixXd::Identity(n - p - q, n - p - q);
            VectorXd sig_temp{sig(seq(p, n - q - 1))};
            VectorXd gamma_temp{gamma(seq(p, n - q - 2))};
            shift_QR_sym(sig_temp, gamma_temp, Q, P);
            U(all, seq(p, n - q - 1)) = U(all, seq(p, n - q - 1)) * P;
            V(all, seq(p, n - q - 1)) = V(all, seq(p, n - q - 1)) * Q;
            sig(seq(p, n - q - 1)) = sig_temp;
            gamma(seq(p, n - q - 2)) = gamma_temp;
        }
        else
        {
            // double delta;//change cofficient
            double y{gamma(k)};
            double z{sig(k + 1)};
            double c;
            double s;
            for (int i = k + 1; i < n; i++)
            {

                s = y / std::pow(y * y + z * z, 0.5);
                c = z / std::pow(y * y + z * z, 0.5);

                sig(i) = s * y + c * z;
                U(all, seq(p, n - q - 1)) = U(all, seq(p, n - q - 1)) * generate_jacobi_matrix(n - p - q, k, i, s, c);

                if (i < n - 1)
                {
                    y = -s * gamma(i);
                    z = sig(i + 1);
                    gamma(i) = c * gamma(i);
                }
            }
        }
        // A = MatrixXd::Zero(m, n);

        for (int i = 0; i < n; i++)
        {

            A(i, i) = sig(i);
            if (i < n - 1)
            {
                A(i, i + 1) = gamma(i);
            }
        }

        // std::cout << "A = " << A << std::endl
        //           << std::endl;

        // std::cout << U * A * V.transpose() - A_0 << std::endl;
        iter++;
    }
    singular = sig;
}
