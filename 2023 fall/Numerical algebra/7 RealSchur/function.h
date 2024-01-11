#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"
using namespace Eigen;

Eigen::MatrixXd generate_jacobi_matrix(int n, int p, int q, double sin_theta, double cos_theta);
Eigen::MatrixXd generate_jacobi_matrix(int p, int q, Eigen::MatrixXd &A);
Eigen::MatrixXd threshold_jacobi_3tr(Eigen::MatrixXd &A, double threshold, int &iter);
Eigen::MatrixXd generate_special_matrix(int n);
int calculate_sign(double r, Eigen::VectorXd &x, Eigen::VectorXd &y);
double bisection_3tri_method(Eigen::MatrixXd &A, int m, int &iter);
Eigen::VectorXd inverse_power_method(Eigen::MatrixXd &A, double lamda);
void read_diagonal(Eigen::MatrixXd &A);
