#pragma once

#include <sstream>
#include <list>
#include <iostream>
#include <climits>
#include <string>

class RPN {
  public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    static bool evaluate(const std::string& expression, long long& result);

  private:
    static bool isOperator(const std::string& token);
};