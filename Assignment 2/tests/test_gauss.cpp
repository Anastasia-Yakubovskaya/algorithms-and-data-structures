#include <gtest/gtest.h>
#include "gauss.h"
#include <fstream>

TEST(GausMethodTest, Standardmatrix) {
    MatrixXd A(3,4);
     A << 2,  1, -1,  8,
        -3, -1,  2, -11,
        -2,  1,  2, -3;
    VectorXd result = methodGauss(A);
    VectorXd expected(3);
    expected << 2, 3, -1;
    for (int i = 0; i < expected.size(); ++i) {
        ASSERT_NEAR(result(i),expected(i), 1e-10);
    }
}


TEST(GausMethodTest, Infinitenumberofsolutions) {
    std::remove("result.csv"); 
    
    MatrixXd A(2,3);
     A << 1,  1, 1,
          2,  2, 2;
          
    VectorXd result = methodGauss(A);
       
    std::ifstream file("result.csv");
    std::string content;
    std::getline(file,content);
    
    ASSERT_EQ(content, "Бесконечное количество решений");
}

TEST(GausMethodTest, nosolutions) {
    std::remove("result.csv"); 
    
    MatrixXd A(2,3);
    A << 1, 1, 1,
         1, 1, 2;
          
    VectorXd result = methodGauss(A);
       
    std::ifstream file("result.csv");
    std::string content;
    std::getline(file,content);
    
    ASSERT_EQ(content, "Нет решений");
}

TEST(GausMethodTest, randomgen) {
    Eigen::MatrixXd A = randomgenerator();
    
    ASSERT_GT(A.rows(), 0);
    ASSERT_EQ(A.cols(), A.rows() + 1);
    
    std::remove("result.csv");
    VectorXd gauss_solution = methodGauss(A);
    
    std::ifstream file("result.csv");
    std::string content;
    std::getline(file, content);
    
    if (content == "Единственное решение") {

        MatrixXd A_part = A.leftCols(A.cols()-1);
        VectorXd b = A.rightCols(1);
        VectorXd calculated_b = A_part * gauss_solution;
        
        for (int i = 0; i < b.size(); ++i) {
            ASSERT_NEAR(calculated_b(i), b(i), 1e-8);
        }
    }
    else if (content == "Нет решений") {
        ASSERT_EQ(gauss_solution.size(), 0);
    }
    else if (content == "Бесконечное количество решений") {
        ASSERT_EQ(gauss_solution.size(), 0);
    }
    else {
        MatrixXd A_part = A.leftCols(A.cols()-1);
        VectorXd b = A.rightCols(1);
        VectorXd calculated_b = A_part * gauss_solution;
        
        for (int i = 0; i < b.size(); ++i) {
            ASSERT_NEAR(calculated_b(i), b(i), 1e-8) ;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
