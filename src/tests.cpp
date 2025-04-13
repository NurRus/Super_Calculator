#include <gtest/gtest.h>

#include "Model/calc_model.h"
#include <string>

class CalculatorModelTest:public::testing::Test{};

TEST_F(CalculatorModelTest, Test_1){
    std::string expr = "2*x/2";
    std::string arg = "2";
    double y = 2 * 2 / 2;
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_2){
    std::string expr = "-256+256*1.34-234.52/42.765";
    std::string arg = "0";
    double y =  -256 + 256 * 1.34 - 234.52 / 42.765;
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_3){
    std::string expr = "(1.213/sqrt(6986.32))^3.5";
    std::string arg = "0";
    double y =  pow(1.213 / sqrt(6986.32), 3.5);
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_4){
    std::string expr = "1/sin(3)+cos(4)/tan(2.45)";
    std::string arg = "0";
    double y =  1 / sin(3) + cos(4) / tan(2.45);
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_5){
    std::string expr = "ln(321.423)/log(3.78)";
    std::string arg = "0";
    double y =  log(321.423) / log10(3.78);
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_6){
    std::string expr = "1.4*asin(0.453)/acos(0.9876)-atan(2)";
    std::string arg = "0";
    double y =  1.4 * asin(0.453) / acos(0.9876) - atan(2);
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_7){
    std::string expr = "44mod3+43.4mod3.7";
    std::string arg = "0";
    double y =  44 % 3 + fmod(43.4, 3.7);
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_8){
    std::string expr = "sin(sqrt((x*sin(x)+cos(x))^3.5))";
    std::string arg = "1.5";
    double x = 1.5;
    double y =  sin(sqrt(pow(x * sin(x) + cos(x), 3.5)));
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_9){
    std::string expr = "sinsqrt((x*sin(x)+cos(x))^3.5)";
    std::string arg = "1.5";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_10){
    std::string expr = "-2+3*x/";
    std::string arg = "1.5";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_11){
    std::string expr = "-2+3*x/cos4";
    std::string arg = "1.5";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_12){
    std::string expr = "1/sin(x)";
    std::string arg = "0";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_DIVISION_BY_ZERO);
}

TEST_F(CalculatorModelTest, Test_13){
    std::string expr = "sqrt(x)";
    std::string arg = "-1";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_SQUARE_ROOT);
}

TEST_F(CalculatorModelTest, Test_14){
    std::string expr = "ln(x)";
    std::string arg = "0";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_LOGARITHM);
}

TEST_F(CalculatorModelTest, Test_15){
    std::string expr = "ln(x)";
    std::string arg = "0";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_LOGARITHM);
}

TEST_F(CalculatorModelTest, Test_16){
    std::string expr = "/+3";
    std::string arg = "0";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_17){
    std::string expr = "3*x/cos()";
    std::string arg = "0";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_18){
    std::string expr = "3*x/cos(x)(-2)";
    std::string arg = "0";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_20){
    std::string expr = "3*sin(abs(x))*x/cos(abs(x))";
    std::string arg = "-1.5";
    double x = -1.5;
    double y =  3 * sin(fabs(x)) * x / cos(fabs(x));
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_21){
    std::string expr = "sin(cos(tan(x)))";
    std::string arg = "-1.5";
    double x = -1.5;
    double y =  sin(cos(tan(x)));
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_NO_ERROR);
    ASSERT_NEAR(mod.getResult(), y, 1e-7);
}

TEST_F(CalculatorModelTest, Test_22){
    std::string expr = "(-2+)3*x/cos4";
    std::string arg = "1.5";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_23){
    std::string expr = "tan(x)";
    std::string arg = "1.570796327";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_TANGENT);
}

TEST_F(CalculatorModelTest, Test_24){
    std::string expr = "3*x1";
    std::string arg = "1.5";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

TEST_F(CalculatorModelTest, Test_25){
    std::string expr = "3.x+5";
    std::string arg = "1.5";
    CALC_Model mod(expr, arg);
    ASSERT_EQ(mod.getError(), CALC_Model::ERROR_INVALID_EXPRESSION);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }