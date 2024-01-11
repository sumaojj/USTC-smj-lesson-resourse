#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

// the problem is min c^T*x s.t. Ax=b,x>=0

struct linear_program_data
{
    MatrixXd A{};      // constraint matrix size=m*n
    VectorXd b{};      // constraint vector size=m*1
    VectorXd c{};      // objective function  size=n*1
    int n{};           // initial n
    VectorXd x_mini{}; // optimal solution
    VectorXi index{};  // for index
    double v{0};       // optimal solution
    int e{0};          // for exchange
    int exitflag{1};   // 1 for solution found , -1 for unbounded, 0 for no feasible solution
};

// delete duplicate bounds
void delete_duplicate_rows(linear_program_data &p)
{
    // check if Ax=b has  solution
    int m = p.A.rows();
    int n = p.A.cols();
    MatrixXd join(m, n + 1);
    join << p.A, p.b;
    FullPivLU<MatrixXd> lu(join);
    FullPivLU<MatrixXd> lA(p.A);
    if (lu.rank() > lA.rank())
    {
        p.exitflag = 0; // no feasible solution
        return;
    }
    if (lA.rank() == n)
    {
        p.exitflag = 1; // solution found
        return;
    }

    HouseholderQR<MatrixXd> qr(p.A.transpose());
    MatrixXd R{qr.matrixQR().triangularView<Upper>()};
    MatrixXd Q{qr.householderQ()};

    // std::cout << R << std::endl;
    // std::cout << Q << std::endl;
    // std::cout << p.A.transpose() - Q * R << std::endl;

    // delete duplicate bounds

    std::vector<int> index; // for storage
    for (int i = 0; i < m; i++)
    {
        if (std::fabs(R(i, i)) > 1e-10)
        {
            index.push_back(i);
        }
    }
    int new_m = index.size();
    MatrixXd new_A(new_m, n);
    VectorXd new_b(new_m);
    for (int i = 0; i < new_m; i++)
    {
        new_A.row(i) = p.A.row(index[i]);
        new_b(i) = p.b(index[i]);
    }
    p.A = new_A;
    p.b = new_b;

    // std::cout << p.A << std::endl;
    // std::cout << p.b.transpose() << std::endl;
    // std::cout << p.c.transpose() << std::endl;
}

// ini_bigM change p,choose M=100000
void ini_bigM(linear_program_data &p)
{

    // std::cout << p.A << std::endl;
    // std::cout << p.b.transpose() << std::endl;
    // std::cout << p.c.transpose() << std::endl;

    const int M = 100000;
    int m = p.A.rows();
    int n = p.A.cols();

    p.x_mini = VectorXd::Zero(n + m);

    p.index = VectorXi::Ones(m);
    for (int i = 0; i < m; i++)
    {
        p.index(i) = n + i;
    }

    VectorXd c_1(m);
    c_1 = M * c_1.setOnes(m);
    VectorXd temp(n + m); // for storage
    temp << p.c, c_1;
    p.c = temp;

    MatrixXd A_1(m, n + m);
    MatrixXd I = MatrixXd::Identity(m, m);
    A_1 << p.A, I;
    p.A = A_1;

    // p.x_B = p.b;

    VectorXd c_B = p.c(p.index);
    p.v = c_B.dot(p.b);

    // std::cout << p.v << std::endl;
    //  std::cout << p.b.transpose() << std::endl;
    // std::cout << p.c.transpose() << std::endl;
}

bool optimal_decision(linear_program_data &p)
{
    int m = p.A.rows();
    int n = p.A.cols() - m;

    VectorXi tempindex = VectorXi::Zero(n + m);
    for (int i = 0; i < m; i++)
    {
        tempindex(p.index(i)) = 1;
    }

    MatrixXd B = p.A(all, p.index);

    VectorXd c_B = p.c(p.index);
    MatrixXd B_t{B.transpose()};

    VectorXd w{B_t.inverse() * c_B};

    p.v = w.dot(p.b);

    // std::cout << w << std::endl;
    p.x_mini(p.index) = B.inverse() * p.b; // have to get proper order using index

    double z;

    for (int i = 0; i < n + m; i++)
    {
        if (tempindex(i) == 0) // i is  in index of N
        {
            z = w.dot(p.A.col(i));
            // indexN(j) = i;

            if (z > p.c(i))
            {
                p.e = i;
                // std::cout << p.e << std::endl;
                return false;
            }
        }
    }

    return true;
}

void Axis_operation(linear_program_data &p)
{
    int m = p.A.rows();
    int n = p.A.cols() - m;

    MatrixXd B = p.A(all, p.index);
    VectorXd y_e = B.inverse() * p.A.col(p.e);
    VectorXd x_B = B.inverse() * p.b;

    // std::cout << y_e << std::endl;
    for (int i = 0; i < m; i++)
    {
        if (y_e(i) > 0)
        {
            break;
        }
        if (i == m - 1)
        {
            p.exitflag = -1; // unbounded
            return;
        }
    }

    int r = 0; // record min r
    bool first = true;
    for (int i = 0; i < m; i++)
    {
        if (y_e(i) > 0 && first == true)
        {
            r = i;
            first = false;
            continue;
        }
        if (y_e(i) > 0)
        {

            if ((x_B(i) / y_e(i)) < (x_B(r) / y_e(r)))
            {
                r = i;
            }
        }
    }
    p.index(r) = p.e;
}

void simplex_method(linear_program_data &p)
{
    delete_duplicate_rows(p);
    ini_bigM(p);
    // std::cout << p.A << std::endl;
    while (optimal_decision(p) == false && p.exitflag != -1)
    {
        Axis_operation(p);
    }
}
