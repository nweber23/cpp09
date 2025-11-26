#include "PmergeMe.hpp"
#include <iostream>

static bool parsePositiveInt(const char *s, unsigned int& out) {
  if (!s || !*s)
    return false;
  char *end = 0;
  unsigned long val = std::strtoul(s, &end, 10);
  if (*end != '\0')
    return false;
  if (val == 0 || val > UINT_MAX)
    return false;
  out = static_cast<unsigned int>(val);
  return true;
}

static double elapsedMicroseconds(const timeval &a, const timeval &b) {
  return (b.tv_sec - a.tv_sec) * 1e6 + (b.tv_usec - a.tv_usec);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::vector<unsigned int> inputVec;
  inputVec.reserve(argc - 1);
  std::set<unsigned int> seen;

  for (int i = 1; i < argc; ++i) {
    unsigned int v;
    if (!parsePositiveInt(argv[i], v)) {
      std::cerr << "Error" << std::endl;
      return 1;
    }
    if (seen.count(v)) {
      std::cerr << "Error" << std::endl;
      return 1;
    }
    seen.insert(v);
    inputVec.push_back(v);
  }

  std::cout << "Before: ";
  for (size_t i = 0; i < inputVec.size(); ++i) {
    std::cout << inputVec[i];
    if (i + 1 < inputVec.size())
      std::cout << " ";
  }
  std::cout << std::endl;

  timeval vStart, vEnd;
  gettimeofday(&vStart, 0);
  std::vector<unsigned int> workVec = inputVec;
  std::vector<unsigned int> sortedVec = PmergeMe::sortVector(workVec);
  gettimeofday(&vEnd, 0);

  timeval dStart, dEnd;
  gettimeofday(&dStart, 0);
  std::deque<unsigned int> workDeq;
  for (size_t i = 0; i < inputVec.size(); ++i)
    workDeq.push_back(inputVec[i]);
  std::deque<unsigned int> sortedDeq = PmergeMe::sortDeque(workDeq);
  gettimeofday(&dEnd, 0);

  std::cout << "After: ";
  for (size_t i = 0; i < sortedVec.size(); ++i) {
    std::cout << sortedVec[i];
    if (i + 1 < sortedVec.size())
      std::cout << " ";
  }
  std::cout << std::endl;

  if (sortedVec.size() != sortedDeq.size()) {
    std::cerr << "Error" << std::endl;
    return 1;
  }
  for (size_t i = 0; i < sortedVec.size(); ++i) {
    if (sortedVec[i] != sortedDeq[i]) {
      std::cerr << "Error" << std::endl;
      return 1;
    }
  }

  double vecMicros = elapsedMicroseconds(vStart, vEnd);
  double deqMicros = elapsedMicroseconds(dStart, dEnd);

  std::cout << "Time to process a range of " << inputVec.size()
            << " elements with std::vector : " << vecMicros << " us" << std::endl;
  std::cout << "Time to process a range of " << inputVec.size()
            << " elements with std::deque  : " << deqMicros << " us" << std::endl;

  return 0;
}