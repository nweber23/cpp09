#pragma once

#include <map>
#include <deque>
#include <vector>
#include <utility>
#include <set>
#include <cstdlib>
#include <climits>
#include <sys/time.h>
#include <algorithm>

class PmergeMe {
  public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    static std::vector<unsigned int> sortVector(const std::vector<unsigned int> &in);
    static std::deque<unsigned int> sortDeque(const std::deque<unsigned int> &in);

  private:
    static std::vector<size_t> buildJacobsthalSequence(size_t limit);

    template<typename Container>
    static size_t binarySearchInsertPos(const Container &sorted, unsigned int value) {
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

    template<typename Container>
    static Container fordJohnson(const Container &in) {
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
          if (a < b)
            std::swap(a, b);
          pairs.push_back(std::make_pair(a, b));
        } else {
          hasPend = true;
          pend = in[i];
        }
      }

      Container highs;
      std::map<unsigned int, unsigned int> highToLow;
      for (size_t i = 0; i < pairs.size(); ++i) {
        highs.push_back(pairs[i].first);
        highToLow[pairs[i].first] = pairs[i].second;
      }

      highs = fordJohnson(highs);

      Container lows;
      for (size_t i = 0; i < highs.size(); ++i)
        lows.push_back(highToLow[highs[i]]);

      Container result = highs;

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
};
