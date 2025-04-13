// calc_model.cpp
#include "calc_model.h"

// Конструктор по умолчанию
CALC_Model::CALC_Model()
    : x(""),
      expression(""),
      result(0.0),
      error(ERROR_NO_ERROR),
      lastPostfix(),
      operatorRegex(R"([+\-*/^m])"),
      functionRegex(R"([sctioaqlgb])") {}

// Конструктор с параметрами
CALC_Model::CALC_Model(const std::string& expr, const std::string& arg)
    : x(arg),
      expression(expr),
      result(0.0),
      error(ERROR_NO_ERROR),
      lastPostfix(),
      operatorRegex(R"([+\-*/^m])"),
      functionRegex(R"([sctioaqlgb])") {
  calculation(expression, x);  // Вычисляем result и error при инициализации
}

void CALC_Model::calculation(std::string& expr, std::string& argument) {
  expression = expr;
  x = argument;

  if (expression.length() > 255) return;

  std::string modifiedExpr = modifiedExpression();

  error = verification(modifiedExpr);
  if (error != ERROR_NO_ERROR) return;

  modifiedExpr = insertSpacesForToken(modifiedExpr);

  std::vector<std::string> postfix = infixToPostfix(modifiedExpr);
  lastPostfix = postfix;

  calculationPostfix(postfix);
}

std::string CALC_Model::modifiedExpression() {
  std::string result, function;
  std::smatch match;
  std::string::const_iterator it(expression.cbegin());
  std::regex functRegex("sin|cos|tan|asin|acos|atan|sqrt|ln|log|abs|mod");

  while (std::regex_search(it, expression.cend(), match, functRegex)) {
    function = match.str();
    function = replaceFunction(function);
    result.append(it, match[0].first);
    result.append(function);
    it = match[0].second;
  }

  result.append(it, expression.cend());

  result = insertZeroByDot(result);
  result = insertZeroBeforeUnary(result);

  return result;
}

// Функция для замены найденных совпадений
std::string CALC_Model::replaceFunction(std::string& funct) {
  if (funct == "sin") return "s";
  if (funct == "cos") return "c";
  if (funct == "tan") return "t";
  if (funct == "asin") return "i";
  if (funct == "acos") return "o";
  if (funct == "atan") return "a";
  if (funct == "sqrt") return "q";
  if (funct == "ln") return "l";
  if (funct == "log") return "g";
  if (funct == "abs") return "b";
  if (funct == "mod") return "m";
  return funct;  // Если не найдено, возвращаем исходное значение
}

// вставка нуля перед точкой или запятой
std::string CALC_Model::insertZeroByDot(std::string& expr) {
  std::string result;
  size_t i = 0;

  for (; i < expr.length(); ++i) {
    if (expr[i] == '.' && (i == 0 || !std::isdigit(expr[i - 1]))) result += '0';
    result += expr[i];
    if (expr[i] == '.' && !std::isdigit(expr[i + 1])) result += '0';
  }

  return result;
}

std::string CALC_Model::insertZeroBeforeUnary(std::string& expr) {
  std::string result;
  size_t i = 0;

  for (; i < expr.length(); ++i) {
    if ((expr[i] == '-') && (i == 0 || expr[i - 1] == '('))
      result += "(0-1)*";
    else if (expr[i] == '+' && (i == 0 || expr[i - 1] == '('))
      result += "";
    else
      result += expr[i];
  }

  return result;
}

CALC_Model::ErrorCode CALC_Model::verification(const std::string& expr) {
  // Проверка на набор символов
  if (containsNonMatchingChar(expr)) return ERROR_INVALID_EXPRESSION;

  size_t i = 0;
  size_t m = -1;
  std::regex digitRegex(R"([0-9])");

  for (; i < expr.length(); ++i) {
    if (std::regex_search(std::string(1, expr[i]), functionRegex))
      if (expr[i + 1] != '(') return ERROR_INVALID_EXPRESSION;
    if (expr[i] == '(' && i > m && !checkBracket(expr, i, &m))
      return ERROR_INVALID_BRACKET;
    if (expr[i] == '(' && expr[i + 1] == ')') return ERROR_INVALID_EXPRESSION;
    if (expr[i] == ')' && expr[i + 1] == '(') return ERROR_INVALID_EXPRESSION;
    if (expr[i] == ')' && i > m) return ERROR_INVALID_BRACKET;
    if (std::regex_search(std::string(1, expr[i]), operatorRegex))
      if (!checkOperator(expr[i + 1])) return ERROR_INVALID_EXPRESSION;
    if (std::regex_search(std::string(1, expr[i]), digitRegex))
      if (!checkDigit(expr[i + 1])) return ERROR_INVALID_EXPRESSION;
    if (expr[i] == 'x' && !checkX(expr[i + 1])) return ERROR_INVALID_EXPRESSION;
  }

  return ERROR_NO_ERROR;
}

bool CALC_Model::containsNonMatchingChar(const std::string& expr) {
  std::regex simvolRegex(R"([+\-*/^()sctioaqlgbm.,0-9x])");
  for (char c : expr) {
    if (!std::regex_search(std::string(1, c), simvolRegex)) {
      return true;  // Найден символ, который не соответствует регулярному
                    // выражению
    }
  }
  return false;  // Все символы соответствуют регулярному выражению
}

bool CALC_Model::checkBracket(const std::string& expr, size_t k, size_t* n) {
  int count = 1;
  size_t i = k + 1;
  if (expr[i] == ')') return false;
  while (count > 0 && i < expr.length()) {
    if (expr[i] == '(') count++;
    if (expr[i] == ')') count--;
    i++;
  }
  *n = i - 1;
  return count == 0 ? true : false;
}

bool CALC_Model::checkOperator(const char& simvol) {
  std::regex digitRegex(R"([x0-9])");
  if (!std::regex_search(std::string(1, simvol), functionRegex))
    if (!std::regex_search(std::string(1, simvol), digitRegex))
      if (simvol != '(') return false;
  return true;
}

bool CALC_Model::checkDigit(const char& simvol) {
  std::regex digitRegex(R"([.,0-9])");
  if (!std::regex_search(std::string(1, simvol), digitRegex))
    if (!std::regex_search(std::string(1, simvol), operatorRegex))
      if (simvol != ')' && simvol != '\0') return false;
  return true;
}

bool CALC_Model::checkX(const char& simvol) {
  std::regex operatorRegex(R"([+\-*/^m])");
  if (!std::regex_search(std::string(1, simvol), operatorRegex))
    if (simvol != ')' && simvol != '\0') return false;
  return true;
}

std::string CALC_Model::insertSpacesForToken(std::string& expr) {
  std::string result;

  size_t i = 0;
  std::regex digitRegex("[0-9.]");
  bool digit = false;

  while (i < expr.length()) {
    while (i < expr.length() &&
           std::regex_search(std::string(1, expr[i]), digitRegex)) {
      result += expr[i];
      i++;
      digit = true;
    }
    if (digit && i < expr.length()) result += ' ';
    result += expr[i];
    if (i < expr.length()) {
      result += ' ';
    }
    i++;
    digit = false;
  }

  return result;
}

std::vector<std::string> CALC_Model::infixToPostfix(const std::string& expr) {
  std::map<char, int> precedence = {{'s', 3},  // s = sin
                                    {'c', 3},  // c = cos
                                    {'t', 3},  // t = tan
                                    {'o', 3},  // o = acos
                                    {'i', 3},  // i = asin
                                    {'a', 3},  // a = atan
                                    {'q', 3},  // q = sqrt
                                    {'l', 3},  // l = ln
                                    {'g', 3},  // g = log
                                    {'b', 3},  // b = abs
                                    {'m', 1},  // m = mod
                                    {'^', 2}, {'*', 1}, {'/', 1},
                                    {'+', 0}, {'-', 0}};
  std::vector<std::string> output;
  std::stack<char> operators;
  std::vector<std::string> tokens = tokenize(expr);
  // Сортировочная станция
  for (const auto& token : tokens) {
    if (precedence.find(token[0]) != precedence.end()) {
      while (!operators.empty() && operators.top() != '(' &&
             precedence[operators.top()] >= precedence[token[0]]) {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
      }
      operators.push(token[0]);
    } else if (token == "(") {
      operators.push('(');
    } else if (token == ")") {
      while (!operators.empty() && operators.top() != '(') {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
      }
      operators.pop();  // удаляем '('
    } else
      output.push_back(token);
  }
  // освобождаем стэк и записываем в строку
  while (!operators.empty()) {
    output.push_back(std::string(1, operators.top()));
    operators.pop();
  }
  return output;
}

std::vector<std::string> CALC_Model::tokenize(const std::string& expr) {
  std::vector<std::string> tokens;
  std::stringstream ss(expr);
  std::string token;

  while (ss >> token) {
    // token = replaceDot(token);
    tokens.push_back(token);
  }

  return tokens;
}

void CALC_Model::calculationPostfix(std::vector<std::string>& expr) {
  std::vector<std::string> postfix_X = insertX(expr, x);

  std::regex digitRegex("[0-9.]");
  std::stack<double> stack;
  double a;
  double res;

  for (const std::string& token : postfix_X) {
    if (std::regex_search(token, digitRegex)) stack.push(std::stod(token));
    if (std::regex_search(token, functionRegex)) {
      a = stack.top();
      stack.pop();
      res = calculationFunction(token, a);
      if (error != ERROR_NO_ERROR) return;
      stack.push(res);
    }
    if (std::regex_search(token, operatorRegex) &&
        !std::regex_search(token, digitRegex)) {
      double b = stack.top();
      stack.pop();
      double a = stack.top();
      stack.pop();
      res = calculationOperator(token, a, b);
      if (error != ERROR_NO_ERROR) return;
      stack.push(res);
    }
  }
  result = stack.top();
}

std::vector<std::string> CALC_Model::insertX(std::vector<std::string>& expr,
                                             std::string& arg) {
  std::vector<std::string> result;

  for (const std::string& token : expr) {
    if (token == "x") {
      result.push_back(arg);
    } else
      result.push_back(token);
  }

  return result;
}

double CALC_Model::calculationFunction(const std::string& function, double a) {
  if (function == "t" && sin(a) == 1) {
    error = ERROR_TANGENT;
    return 0.0;
  }

  if ((function == "l" || function == "g") && a <= 0) {
    error = ERROR_LOGARITHM;
    return 0.0;
  }

  if (function == "q" && a < 0) {
    error = ERROR_SQUARE_ROOT;
    return 0.0;
  }

  if ((function == "i" || function == "o") && (a < -1 || a > 1)) {
    error = ERROR_ARC_SIN_COS;
    return 0.0;
  }

  double res = 0.0;

  if (function == "s") res = sin(a);
  if (function == "c") res = cos(a);
  if (function == "t") res = tan(a);
  if (function == "o") res = acos(a);
  if (function == "i") res = asin(a);
  if (function == "a") res = atan(a);
  if (function == "l") res = log(a);
  if (function == "g") res = log10(a);
  if (function == "q") res = sqrt(a);
  if (function == "b") res = fabs(a);

  return res;
}

double CALC_Model::calculationOperator(const std::string& oper, double a,
                                       double b) {
  if ((oper == "/" || oper == "m") && b == 0) {
    error = ERROR_DIVISION_BY_ZERO;
    return 0.0;
  }

  double res = 0.0;

  if (oper == "+") res = a + b;
  if (oper == "-") res = a - b;
  if (oper == "*") res = a * b;
  if (oper == "/") res = a / b;
  if (oper == "^") res = pow(a, b);
  if (oper == "m") res = fmod(a, b);

  return res;
}

CALC_Model::ErrorCode CALC_Model::getError() { return error; }

double CALC_Model::getResult() { return result; }

double CALC_Model::getResult(std::string& arg) {
  x = arg;
  calculationPostfix(lastPostfix);
  return result;
}

double CALC_Model::getResult(std::string& expr, std::string& arg) {
  calculation(expr, arg);
  return result;
}

CALC_Model::ErrorCode CALC_Model::getError(std::string& expr,
                                           std::string& arg) {
  calculation(expr, arg);
  return error;
}

std::string CALC_Model::getErrorMessage(ErrorCode code) {
  switch (code) {
    case ERROR_NO_ERROR:
      return "No error";
    case ERROR_LONG_EXPRESSION:
      return "Expression is too long";
    case ERROR_INVALID_EXPRESSION:
      return "Invalid expression";
    case ERROR_INVALID_BRACKET:
      return "Invalid bracket";
    case ERROR_DIVISION_BY_ZERO:
      return "Division by zero";
    case ERROR_LOGARITHM:
      return "Logarithm error";
    case ERROR_SQUARE_ROOT:
      return "Square root error";
    case ERROR_TANGENT:
      return "Tangent error";
    case ERROR_ARC_SIN_COS:
      return "Arc sine or cosine error";
    default:
      return "Unknown error";
  }
}

void CALC_Model::reset() {
  result = 0.0;
  error = ERROR_NO_ERROR;
  expression = "";
  lastPostfix.clear();
  x = "";
}
