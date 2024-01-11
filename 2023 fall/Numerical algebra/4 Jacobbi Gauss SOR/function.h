#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

VectorXd Jacobi_iteration_solve(MatrixXd &A, VectorXd &b, double epsilon, int &iter_num);
VectorXd Gauss_Seidel_iteration_solve(MatrixXd &A, VectorXd &b, double epsilon, int &iter_num);
VectorXd SOR_iteration_solve(MatrixXd &A, VectorXd &b, double epsilon, double w, int &iter_num);

MatrixXd Jacobi_iteration_solve(int N, double epsilon, int &iter_num);
MatrixXd Gauss_Seidel_iteration_solve(int N, double epsilon, int &iter_num);
MatrixXd SOR_iteration_solve(int N, double epsilon, double w, int &iter_num);

MatrixXd generate_matrix_1(double aipu);
VectorXd generate_vector_1(double aipu);
VectorXd generate_accurate(double aipu);

void test_jacobi(double aipu);
void test_GS(double aipu);
void test_SOR(double aipu);

void test_jacobi(int N);
void test_GS(int N);
void test_SOR(int N);