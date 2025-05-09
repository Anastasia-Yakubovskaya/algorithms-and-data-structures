#ifndef GAUSS_H
#define GAUSS_H

#include <Eigen/Dense>
#include <string>

using Eigen::MatrixXd;
using Eigen::VectorXd;

Eigen::Matrix<double, -1, -1, Eigen::RowMajor> readsaveCSV(const std::string& filename);
VectorXd methodGauss(const MatrixXd& A);
void writeanswerCSV(const VectorXd& x, const std::string& info);

#endif
