#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {
  (void)other;
}

RPN& RPN::operator=(const RPN& other) {
  (void)other;
  return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) {
  return token == "+" || token == "-" || token == "*" || token == "/";
}

static bool validNumber(const std::string& token, long long& number) {
  if(token.size() != 1 || token[0] < '0' || token[0] > '9')
    return false;
  number = static_cast<long long>(token[0] - '0');
  return true;
}

bool RPN::evaluate(const std::string& expression, long long& result) {
  std::istringstream iss(expression);
  std::string token;
  std::vector<long long> stack;

  while(iss >> token) {
    if(isOperator(token)) {
      if(stack.size() < 2) {
        return false;
      }
      long long b = stack.back(); stack.pop_back();
      long long a = stack.back(); stack.pop_back();
      long long res;
      if(token == "+") {
        res = a + b;
      } else if(token == "-") {
        res = a - b;
      } else if(token == "*") {
        res = a * b;
      } else if(token == "/") {
        if(b == 0) {
          return false;
        }
        res = a / b;
      }
      stack.push_back(res);
    } else {
      long long number;
      if(!validNumber(token, number)) {
        return false;
      }
      stack.push_back(number);
    }
  }
  if(stack.size() != 1) {
    return false;
  }
  result = stack.back();
  return true;
}