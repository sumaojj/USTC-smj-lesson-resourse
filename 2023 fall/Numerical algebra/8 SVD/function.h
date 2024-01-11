#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

Eigen::MatrixXd generate_jacobi_matrix(int n, int p, int q, double sin_theta, double cos_theta);
void house_e1(Eigen::VectorXd &x, Eigen::VectorXd &v, double &beta);
void Didiagonalization(Eigen::MatrixXd &A, Eigen::MatrixXd &U, Eigen::MatrixXd &V);
void shift_QR_sym(Eigen::VectorXd &sig, Eigen::VectorXd &gamma, Eigen::MatrixXd &Q, Eigen::MatrixXd &P);
void SVD_method(MatrixXd &A, int &iter, MatrixXd &U, MatrixXd &V, VectorXd &singular);

#endif // FUNCTION_H