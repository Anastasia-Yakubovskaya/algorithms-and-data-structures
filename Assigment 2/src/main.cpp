#include <iostream>
#include "gauss.h"
#include <fstream>

int main() {
    Eigen::MatrixXd A = readsaveCSV("data.csv");        
    VectorXd solution = methodGauss(A);
    std::ifstream result_file("result.csv");
    std::string result_info;
    std::getline(result_file, result_info);
        
    return 0;

}
