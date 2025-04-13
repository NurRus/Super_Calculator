// calc_model.h
#ifndef CALC_MODEL_H
#define CALC_MODEL_H

#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

class CALC_Model {
 public:
  enum ErrorCode {
    ERROR_NO_ERROR = 0,
    ERROR_LONG_EXPRESSION,
    ERROR_INVALID_EXPRESSION,
    ERROR_INVALID_BRACKET,
    ERROR_DIVISION_BY_ZERO,
    ERROR_LOGARITHM,
    ERROR_SQUARE_ROOT,
    ERROR_TANGENT,
    ERROR_ARC_SIN_COS
  };

 private:
  std::string x;
  std::string expression;
  double result;
  ErrorCode error;
  std::vector<std::string> lastPostfix;
  std::regex operatorRegex;
  std::regex functionRegex;

 public:
  // Конструктор по умолчанию
  CALC_Model();
  // Конструктор с параметрами
  CALC_Model(const std::string& expr, const std::string& arg);
  ~CALC_Model() {}

  void calculation(std::string& expr, std::string& argument);
  ErrorCode getError();
  ErrorCode getError(std::string& expr, std::string& arg);
  std::string getErrorMessage(ErrorCode code);
  double getResult();
  double getResult(std::string& arg);
  double getResult(std::string& expr, std::string& arg);
  void reset();

 private:
  std::string modifiedExpression();
  std::string replaceFunction(std::string& funct);
  std::string insertZeroByDot(std::string& expr);
  std::string insertZeroBeforeUnary(std::string& expr);
  ErrorCode verification(const std::string& expr);
  bool containsNonMatchingChar(const std::string& expression);
  bool checkBracket(const std::string& expression, size_t k, size_t* n);
  bool checkOperator(const char& simvol);
  bool checkDigit(const char& simvol);
  bool checkX(const char& simvol);
  std::string insertSpacesForToken(std::string& expr);
  std::vector<std::string> infixToPostfix(const std::string& expr);
  std::vector<std::string> tokenize(const std::string& expr);
  std::vector<std::string> insertX(std::vector<std::string>& expr,
                                   std::string& arg);
  void calculationPostfix(std::vector<std::string>& expr);
  double calculationFunction(const std::string& function, double a);
  double calculationOperator(const std::string& oper, double a, double b);
};

#endif  // CALC_MODEL_H
