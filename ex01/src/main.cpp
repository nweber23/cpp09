#include "RPN.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " \"expression\"" << std::endl;
    return 1;
  }
  long long result;
  if (!RPN::evaluate(argv[1], result)) {
    std::cout << "Error: invalid expression." << std::endl;
    return 1;
  }
  std::cout << "Result: " << result << std::endl;
  return 0;
}