#include <iostream>
#include "gauss.h"

int main() {
    try {
        Eigen::MatrixXd A = readsaveCSV("data.csv");
        std::cout << "Matrix A:\n" << A << std::endl;
        
        Eigen::VectorXd solution = methodGauss(A);
        std::cout << "Solution:\n" << solution << std::endl;
        
        writeanswerCSV(solution);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
