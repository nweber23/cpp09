#include "PmergeMe.hpp"

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