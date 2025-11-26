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

size_t PmergeMe::binarySearchInsertPos(const std::vector<unsigned int> &sorted, unsigned int value) {
  size_t low = 0;
  size_t high = sorted.size();
  while (low < high) {
    size_t mid = (low + high) / 2;
    if (sorted[mid] < value)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}

size_t PmergeMe::binarySearchInsertPosDeque(const std::deque<unsigned int> &sorted, unsigned int value) {
  size_t low = 0;
  size_t high = sorted.size();
  while (low < high) {
    size_t mid = (low + high) / 2;
    if (sorted[mid] < value)
      low = mid + 1;
    else
      high = mid;
  }
  return low;
}

std::vector<unsigned int> PmergeMe::fordJohnsonVector(const std::vector<unsigned int> &in) {
  size_t n = in.size();
  if (n <= 1)
    return in;
  std::vector< std::pair<unsigned int, unsigned int> > pairs;
  bool hasPend = false;
  unsigned int pend = 0;

  for (size_t i = 0; i < n; i += 2) {
    if (i + 1 < n) {
      unsigned int a = in[i];
      unsigned int b = in[i + 1];
      if (a < b) {
        unsigned int tmp = a;
        a = b;
        b = tmp;
      }
      pairs.push_back(std::make_pair(a, b));
    } else {
      hasPend = true;
      pend = in[i];
    }
  }

  std::vector<unsigned int> highs;
  highs.reserve(pairs.size());
  std::map<unsigned int, unsigned int> highToLow;
  for (size_t i = 0; i < pairs.size(); ++i) {
    highs.push_back(pairs[i].first);
    highToLow[pairs[i].first] = pairs[i].second;
  }

  highs = fordJohnsonVector(highs);

  std::vector<unsigned int> lows;
  lows.reserve(highs.size());
  for (size_t i = 0; i < highs.size(); ++i)
    lows.push_back(highToLow[highs[i]]);

  std::vector<unsigned int> result = highs;

  size_t m = lows.size();
  if (m) {
    std::vector<size_t> jacob = buildJacobsthalSequence(m);
    std::vector<size_t> order;
    size_t last = 0;
    for (size_t j = 0; j < jacob.size(); ++j) {
      size_t cur = jacob[j];
      for (size_t k = cur; k > last; --k)
        order.push_back(k);
      last = cur;
    }
    for (size_t k = m; k > last; --k)
      order.push_back(k);

    for (size_t idx = 0; idx < order.size(); ++idx) {
      size_t pos = order[idx];
      if (pos == 0 || pos > m)
        continue;
      unsigned int val = lows[pos - 1];
      size_t ins = binarySearchInsertPos(result, val);
      result.insert(result.begin() + ins, val);
    }
  }

  if (hasPend) {
    size_t ins = binarySearchInsertPos(result, pend);
    result.insert(result.begin() + ins, pend);
  }

  return result;
}

std::vector<unsigned int> PmergeMe::sortVector(const std::vector<unsigned int> &in) {
  return fordJohnsonVector(in);
}

std::deque<unsigned int> PmergeMe::fordJohnsonDeque(const std::deque<unsigned int> &in) {
  size_t n = in.size();
  if (n <= 1)
    return in;
  std::vector< std::pair<unsigned int, unsigned int> > pairs;
  bool hasPend = false;
  unsigned int pend = 0;

  for (size_t i = 0; i < n; i += 2) {
    if (i + 1 < n) {
      unsigned int a = in[i];
      unsigned int b = in[i + 1];
      if (a < b) {
        unsigned int tmp = a;
        a = b;
        b = tmp;
      }
      pairs.push_back(std::make_pair(a, b));
    } else {
      hasPend = true;
      pend = in[i];
    }
  }

  std::deque<unsigned int> highs;
  std::map<unsigned int, unsigned int> highToLow;
  for (size_t i = 0; i < pairs.size(); ++i) {
    highs.push_back(pairs[i].first);
    highToLow[pairs[i].first] = pairs[i].second;
  }

  highs = fordJohnsonDeque(highs);

  std::deque<unsigned int> lows;
  for (size_t i = 0; i < highs.size(); ++i)
    lows.push_back(highToLow[highs[i]]);
  std::deque<unsigned int> result = highs;

  size_t m = lows.size();
  if (m) {
    std::vector<size_t> jacob = buildJacobsthalSequence(m);
    std::vector<size_t> order;
    size_t last = 0;
    for (size_t j = 0; j < jacob.size(); ++j) {
      size_t cur = jacob[j];
      for (size_t k = cur; k > last; --k)
        order.push_back(k);
      last = cur;
    }
    for(size_t k = m; k > last; --k)
      order.push_back(k);

    for (size_t idx = 0; idx < order.size(); ++idx) {
      size_t pos = order[idx];
      if (pos == 0 || pos > m)
        continue;
      unsigned int val = lows[pos - 1];
      size_t ins = binarySearchInsertPosDeque(result, val);
      result.insert(result.begin() + ins, val);
    }
  }

  if (hasPend) {
    size_t ins = binarySearchInsertPosDeque(result, pend);
    result.insert(result.begin() + ins, pend);
  }
  return result;
}

std::deque<unsigned int> PmergeMe::sortDeque(const std::deque<unsigned int> &in) {
  return fordJohnsonDeque(in);
}