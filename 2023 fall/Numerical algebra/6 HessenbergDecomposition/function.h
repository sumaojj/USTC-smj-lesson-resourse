#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

// input from x^0 to x^n
MatrixXd generate_Companion_Matrix(VectorXd &a)
{
    int n = a.rows() - 1;
    MatrixXd C = MatrixXd::Zero(n, n);
    for (int i = 0; i < n - 1; i++)
    {
        C(i + 1, i) = 1;
    }
    for (int i = 0; i < n; i++)
    {
        C(0, i) = -a(n - i - 1) / a(n);
    }

    return C;
}

double power_method(MatrixXd &A, int &iter)
{
    int n = A.rows();
    VectorXd q = VectorXd::Zero(n);
    q(n - 1) = 1;
    VectorXd y = A * q;
    double lambda = 0;

    for (int i = 0; i < iter; i++)
    {
        q = y / y.norm();
        y = A * q;
        lambda = q.transpose() * y;
    }

    return lambda;
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
// qr decomposition
MatrixXd QR_factorization_2(MatrixXd &A)
{
    VectorXd v(2);
    VectorXd u{A(seq(0, 1), 0)};
    double beta = 0;
    house_e1(u, v, beta);

    MatrixXd Q{MatrixXd::Identity(2, 2) - beta * v * v.transpose()};
    return Q;
}

MatrixXd QR_method_2(MatrixXd &H, int iter)
{

    // QR method for 2*2 matrix
    int n = H.rows();
    MatrixXd Q = MatrixXd::Identity(n, n);
    for (int i = 0; i < iter; i++)
    {
        MatrixXd Q_0{QR_factorization_2(H)};
        // std::cout << Q_0 << std::endl;
        H = Q_0 * H * Q_0.transpose();
        Q = Q_0 * Q;
    }
    return Q.transpose();
}

void hessenberg_decomposition(MatrixXd &A)
{
    int n = A.rows();
    // std::cout << A << std::endl;
    // std::cout << "----------------" << std::endl;
    VectorXd v{VectorXd::Ones(n)};
    double beta = 0;
    for (int k = 0; k < n - 2; k++)
    {
        VectorXd A_0{A(seq(k + 1, n - 1), k)};
        VectorXd v_0{v(seq(k + 1, n - 1))};
        house_e1(A_0, v_0, beta);

        A(seq(k + 1, n - 1), seq(k, n - 1)) = (MatrixXd::Identity(n - k - 1, n - k - 1) - beta * v_0 * v_0.transpose()) * A(seq(k + 1, n - 1), seq(k, n - 1));
        A(seq(0, n - 1), seq(k + 1, n - 1)) = A(seq(0, n - 1), seq(k + 1, n - 1)) * (MatrixXd::Identity(n - k - 1, n - k - 1) - beta * v_0 * v_0.transpose());
        // std::cout << A << std::endl;
        // std::cout << "----------------" << std::endl;
    }

    // let A be Hessenberg matrix
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 2; j < n; j++)
        {
            A(j, i) = 0;
        }
    }
}

bool isrealblock(MatrixXd &A)
{
    // defualt n==2
    double trace = A(0, 0) + A(1, 1);
    double det = A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0);
    return (trace * trace - 4 * det >= 0);
}

MatrixXd francis_double_shift(MatrixXd &H)
{

    int n = H.rows();
    if (n == 2)
    {
        MatrixXd Q{QR_method_2(H, 15)};
        return Q;
    }

    int m = n - 1;
    double s = H(m - 1, m - 1) + H(m, m);
    double t = H(m - 1, m - 1) * H(m, m) - H(m - 1, m) * H(m, m - 1);
    double x = H(0, 0) * H(0, 0) + H(0, 1) * H(1, 0) - s * H(0, 0) + t;
    double y = H(1, 0) * (H(0, 0) + H(1, 1) - s);
    double z = H(1, 0) * H(2, 1);
    double beta = 0;
    VectorXd v(3);

    MatrixXd Q = MatrixXd::Identity(n, n);

    for (int k = -1; k < n - 3; k++)
    {
        VectorXd u(3);
        u << x, y, z;

        house_e1(u, v, beta);
        int q = std::max(0, k);
        H(seq(k + 1, k + 3), seq(q, n - 1)) = (MatrixXd::Identity(3, 3) - beta * v * v.transpose()) * H(seq(k + 1, k + 3), seq(q, n - 1));
        // std::cout << H << std::endl;
        int r = std::min(k + 4, n - 1);
        H(seq(0, r), seq(k + 1, k + 3)) = H(seq(0, r), seq(k + 1, k + 3)) * (MatrixXd::Identity(3, 3) - beta * v * v.transpose());
        // std::cout << H << std::endl;
        Q(seq(0, r), seq(k + 1, k + 3)) = Q(seq(0, r), seq(k + 1, k + 3)) * (MatrixXd::Identity(3, 3) - beta * v * v.transpose());

        x = H(k + 2, k + 1);
        y = H(k + 3, k + 1);
        if (k < n - 4)
        {
            z = H(k + 4, k + 1);
        }
    }

    VectorXd u_0(2);
    u_0 << x, y;
    VectorXd v_0(2);
    house_e1(u_0, v_0, beta);

    H(seq(n - 2, n - 1), seq(n - 3, n - 1)) = (MatrixXd::Identity(2, 2) - beta * v_0 * v_0.transpose()) * H(seq(n - 2, n - 1), seq(n - 3, n - 1));
    // std::cout << H << std::endl;
    H(seq(0, n - 1), seq(n - 2, n - 1)) = H(seq(0, n - 1), seq(n - 2, n - 1)) * (MatrixXd::Identity(2, 2) - beta * v_0 * v_0.transpose());
    // std::cout << H << std::endl;
    Q(seq(0, n - 1), seq(n - 2, n - 1)) = Q(seq(0, n - 1), seq(n - 2, n - 1)) * (MatrixXd::Identity(2, 2) - beta * v_0 * v_0.transpose());

    return Q;
}

int Schur_decomposition(MatrixXd &A)
{
    hessenberg_decomposition(A);
    int n = A.rows();
    int m = n;
    int l = 0;
    int iter = 0;

    // std::cout << A << std::endl;
    // std::cout << "----------------" << std::endl;
    while (true)
    {
        m = n;
        l = 0;

        for (int i = 0; i < n - 2; i++)
        {
            for (int j = i + 2; j < n; j++)
            {
                A(j, i) = 0;
            }
        }

        for (int i = 0; i < n - 1; i++)
        {
            if (abs(A(i + 1, i)) < (abs(A(i, i)) + abs(A(i + 1, i + 1))) * 1e-12)
            {
                A(i + 1, i) = 0;
            }
        }

        for (int i = n - 2; i >= 1; i--)
        {
            MatrixXd block{A(seq(i - 1, i), seq(i - 1, i))};
            if ((A(i + 1, i) != 0) && (A(i, i - 1) != 0))
            {

                m = n - i - 2;
                break;
            }
            if ((A(i + 1, i) == 0) && (A(i, i - 1) != 0) && isrealblock(block))
            {
                m = n - i - 1;
                break;
            }
        }

        for (int i = 1; i < n - 1; i++)
        {
            MatrixXd block{A(seq(i - 1, i), seq(i - 1, i))};
            if ((A(i + 1, i) != 0) && (A(i, i - 1) != 0))
            {
                l = i - 1;
                break;
            }
            if ((A(i + 1, i) == 0) && (A(i, i - 1) != 0) && isrealblock(block))
            {
                l = i;
                break;
            }
        }
        // std::cout << A << std::endl;
        // std::cout << "----------------" << std::endl;

        if (m == n)
        {
            break;
        }

        MatrixXd A_0{A(seq(l, n - m - 1), seq(l, n - m - 1))};
        MatrixXd P{francis_double_shift(A_0)};
        // std::cout << P << std::endl;
        iter++;
        // std::cout << A << std::endl;
        //     std::cout << "----------------" << std::endl;

        A(seq(l, n - m - 1), seq(l, n - m - 1)) = P.transpose() * A(seq(l, n - m - 1), seq(l, n - m - 1)) * P;
        // std::cout << P << std::endl;
        //  std::cout << (A(seq(l, n - m - 1), seq(l, n - m - 1)) - A_0) << std::endl;
        if (l == 0 && m == 0)
        {
            continue;
        }

        if (l == 0)
        {
            A(seq(l, n - m - 1), seq(n - m, n - 1)) = P.transpose() * A(seq(l, n - m - 1), seq(n - m, n - 1));
            continue;
        }

        if (m == 0)
        {
            A(seq(0, l - 1), seq(l, n - m - 1)) = A(seq(0, l), seq(l, n - m - 1)) * P;
            continue;
        }

        A(seq(0, l - 1), seq(l, n - m - 1)) = A(seq(0, l), seq(l, n - m - 1)) * P;

        A(seq(l, n - m - 1), seq(n - m, n - 1)) = P.transpose() * A(seq(l, n - m - 1), seq(n - m, n - 1));
    }
    return iter;
}

void read_schur(MatrixXd &A)
{
    int n = A.rows();
    std::vector<double> lambda;
    std::vector<double> mu;
    for (int i = 0; i < n; i++)
    {
        lambda.push_back(A(i, i));
        if (i < n - 1)
        {
            mu.push_back(A(i + 1, i));
        }
    }
    mu.push_back(0);

    for (int i = 0; i < n; i++)
    {
        if (abs(mu[i]) < 1e-12)
        {
            std::cout << "lambda = " << lambda[i] << std::endl;
        }
        else
        {
            double a = 1;
            double trace = lambda[i] + lambda[i + 1];
            double det = lambda[i] * lambda[i + 1] - mu[i] * A(i, i + 1);
            double delta = trace * trace - 4 * det;
            lambda[i] = trace / 2;
            mu[i] = pow(-delta, 0.5) / 2;
            std::cout << "lambda = " << lambda[i] << " + " << mu[i] << " i" << std::endl;
            std::cout << "lambda = " << lambda[i] << " - " << mu[i] << " i" << std::endl;
            i++;
        }
    }
}
