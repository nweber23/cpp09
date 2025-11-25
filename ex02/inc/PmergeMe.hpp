#pragma once

#include <map>
#include <deque>
#include <vector>
#include <utility>
#include <set>
#include <cstdlib>
#include <climits>
#include <sys/time.h>

class PmergeMe {
  public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    static std::vector<unsigned int> sortVector(const std::vector<unsigned int> &in);
    static std::vector<unsigned int> sortDeque(const std::deque<unsigned int> &in);
  private:
    static std::vector<unsigned int> fordJohnsonVector(const std::vector<unsigned int> &in);
    static std::vector<unsigned int> fordJohnsonDeque(const std::vector<unsigned int> &in);
    static size_t binarySearchInsertPos(const std::vector<unsigned int> $sorted, unsigned int value);
    static size_t binarySearchInsertPosDeque(const std::vector<unsigned int> $sorted, unsigned int value);

    static std::vector<size_t> buildJacobsthalSequence(size_t limit);
};