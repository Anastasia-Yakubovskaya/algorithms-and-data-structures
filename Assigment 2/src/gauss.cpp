#include "gauss.h"
#include <iostream>
#include <fstream>
#include <iomanip>  
#include <lazycsv.hpp>  


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
    MatrixXd Ab = A; 

    for (int i = 0; i < n; ++i) {
            while (Ab(i,i) == 0){
    	        for (int j = i+1; j<n; ++j) {
    	            if (Ab(j,i) != 0) {
    	                Ab.row(i).swap(Ab.row(j));
    	                break;
    	            }
    	        }
    	}
        double diag_el = Ab(i, i);
        Ab.row(i) /= diag_el;

        for (int k = i + 1; k < n; ++k) {
            double kof = Ab(k, i);
            Ab.row(k) -= kof * Ab.row(i);
        }
    }
    

    VectorXd x(n);
    for (int i = n - 1; i >= 0; --i) {
        x(i) = Ab(i, n );
        for (int j = i + 1; j < n; ++j) {
            x(i) -= Ab(i, j) * x(j);
        }
    }
    
    return x;
}

void writeanswerCSV(const VectorXd& x) {
    std::ofstream file("result.csv");
    
    if (file.is_open()) {
        file << std::setprecision(15);
        for (int i = 0; i < x.size(); ++i) {
            file << x(i);
            if (i != x.size() - 1) {
                file << " ";
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for writing!" << std::endl;
    }
}
