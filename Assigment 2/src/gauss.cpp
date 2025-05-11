#include "gauss.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <lazycsv.hpp>
#include <random>

#define EIGEN_VECTORIZE_SSE4
#define EIGEN_VECTORIZE_AVX
#pragma GCC optimize("O3")

Eigen::Matrix<double, -1, -1, Eigen::RowMajor> readsaveCSV(const std::string& filename) {
    std::vector<std::vector<double>> rcsv;
    lazycsv::parser parser(filename);  
    for (const auto row: parser) {
        std::vector<double> r {};
        for (const auto cell : row) {
            r.push_back(std::stod(std::string(cell.raw())));
        }
        rcsv.push_back(r);
    }
    
    Eigen::Matrix<double, -1, -1, Eigen::RowMajor> A(rcsv.size(), rcsv.begin()->size());
        
    int ir = 0;
    for (auto r: rcsv) {
        int ic = 0;
        for(double e: r) {
            A(ir, ic++) = e;
        }
        ir++;
    }
    
    return A;
}

VectorXd methodGauss(const MatrixXd& A) {
    int n = A.rows();
    int m = A.cols() - 1;
    MatrixXd Ab = A;
    int solution_flag = 1; 
    

    for (int i = 0; i < n; ++i) {
        if (Ab(i,i) == 0) {
            int found_flag = 0;
            for (int j = i+1; j < n; ++j) {
                if (Ab(j,i) != 0) {
                    Ab.row(i).swap(Ab.row(j));
                    found_flag = 1;
                    break;
                }
            }
            if (found_flag == 0) {
                if (Ab(i,m) != 0) {
                    solution_flag = 0;
                    break;
                } else {
                    solution_flag = -1;
                }
                continue;
            }
        }
       
        double pivot = Ab(i,i);
        #pragma omp simd
        for (int k = i; k < Ab.cols(); ++k) {
            Ab(i,k) /= pivot;
        }
        
        #pragma omp parallel for
        for (int k = i+1; k < n; ++k) {
            double factor = Ab(k,i);
            #pragma omp simd
            for (int l = i; l < Ab.cols(); ++l) {
                Ab(k,l) -= factor * Ab(i,l);
            }
        }
    }
    
    if (solution_flag == 1) {
        int zero_row_flag = 0;
        for (int i = 0; i < n; ++i) {
            int all_zero_flag = 1;
            for (int j = 0; j < m; ++j) {
                if (Ab(i,j) != 0) {
                    all_zero_flag = 0;
                    break;
                }
            }
            if (all_zero_flag == 1 && Ab(i,m) == 0) {
                zero_row_flag = 1;
            }
        }
        
        if (zero_row_flag == 1 || m > n) {
            solution_flag = -1;
        }
    }
    
    VectorXd x(m);
    if (solution_flag == 1) {
        for (int i = n-1; i >= 0; --i) {
            x(i) = Ab(i,m);
            #pragma omp simd
            for (int j = i+1; j < m; ++j) {
                x(i) -= Ab(i,j) * x(j);
            }
        }
        writeanswerCSV(x, "Единственное решение");
    } 
    else if (solution_flag == 0) {
        writeanswerCSV(VectorXd(), "Нет решений");
    }
    else {
        writeanswerCSV(VectorXd(), "Бесконечное количество решений");
    }
    
    return x;
}

void writeanswerCSV(const VectorXd& x, const std::string& info) {
    std::ofstream file("result.csv");
    
    if (file.is_open()) {
        file << std::setprecision(15);
        if (x.size() > 0) {
            for (int i = 0; i < x.size(); ++i) {
                file << x(i);
                if (i != x.size() - 1) {
                    file << " ";
                }
            }
        } else {
            file << info;
        }
        file.close();
    }
}


Eigen::Matrix<double, -1, -1, Eigen::RowMajor> randomgenerator() {
    const int rows = rand() % 100 + 3;  
    const int cols = rows + 1;         
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-100, 100);  
    
    Eigen::Matrix<double, -1, -1, Eigen::RowMajor> matrix(rows, cols);
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix(i,j) = dist(gen);    
        }
    }        
    return matrix;
}

