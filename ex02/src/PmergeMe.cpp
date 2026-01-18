#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
  (void)other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
  (void)other;
  return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<size_t> PmergeMe::buildJacobsthalSequence(size_t limit) {
  std::vector<size_t> seq;
  if (limit == 0)
    return seq;
  size_t j1 = 1;
  size_t j2 = 1;
  if (j1 <= limit)
    seq.push_back(j1);
  if (j2 <= limit)
    seq.push_back(j2);
  while (true) {
    size_t next = j2 + 2 * j1;
    if (next > limit)
      break;
    seq.push_back(next);
    j1 = j2;
    j2 = next;
  }
  if (seq.size() > 1 && seq[0] == 1 && seq[1] == 1) {
    seq.erase(seq.begin() + 1);
  }
  return seq;
}

std::vector<unsigned int> PmergeMe::sortVector(const std::vector<unsigned int> &in) {
  return fordJohnson(in);
}

std::deque<unsigned int> PmergeMe::sortDeque(const std::deque<unsigned int> &in) {
  return fordJohnson(in);
}
