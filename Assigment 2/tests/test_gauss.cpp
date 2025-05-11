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
    ASSERT_EQ(A.cols(), A.rows() + 1) ;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
