#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : rates(other.rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
  if (this != &other)
    rates = other.rates;
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadDatabase(const std::string& path) {
  std::ifstream f(path.c_str());
  if(!f.is_open())
    return false;
  std::string line;
  if(!std::getline(f, line))
    return false;
  while(std::getline(f, line)) {
    if(line.empty())
      continue;
    std::size_t comma = line.find(',');
    if(comma == std::string::npos)
      continue;
    std::string date = line.substr(0, comma);
    std::string rateStr = line.substr(comma + 1);
    double rate = std::strtod(rateStr.c_str(), 0);
    if(validDateFormat(date) && validDateFields(date))
      rates[date] = rate;
  }
  return !rates.empty();
}

void BitcoinExchange::processInputFile(const std::string& path) const {
  std::ifstream f(path.c_str());
  if(!f.is_open()) {
    std::cout << "Error: could not open file." << std::endl;
    return;
  }
  std::string line;
  bool first = true;
  while(std::getline(f, line)) {
    if(first) { first = false; if (trim(line) == "date | value") continue; }
    handleLine(line);
  }
}

std::string BitcoinExchange::trim(const std::string& s) {
  std::size_t b = s.find_first_not_of(" \t\r\n");
  if (b == std::string::npos)
    return "";
  std::size_t e = s.find_last_not_of(" \t\r\n");
  return s.substr(b, e - b + 1);
}

bool BitcoinExchange::parseValue(const std::string& token, double& out) {
  char* end = 0;
  out = std::strtod(token.c_str(), &end);
  if (end == token.c_str() || *end != '\0')
    return false;
  return true;
}

bool BitcoinExchange::validDateFormat(const std::string& d) {
  if(d.size() != 10 || d[4] != '-' || d[7] != '-')
    return false;
  for(size_t i = 0; i < d.size(); ++i)
    if(i != 4 && i != 7 && (d[i] < '0' || d[i] > '9'))
      return false;
  return true;
}

bool BitcoinExchange::isLeap(int y) {
  return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool BitcoinExchange::validDateFields(const std::string& d) {
  if (!validDateFormat(d)) return false;
  int y = std::atoi(d.substr(0,4).c_str());
  int m = std::atoi(d.substr(5,2).c_str());
  int day = std::atoi(d.substr(8,2).c_str());
  if (m < 1 || m > 12) return false;
  int mdays[] = {31, (isLeap(y)?29:28),31,30,31,30,31,31,30,31,30,31};
  if (day < 1 || day > mdays[m-1]) return false;
  return true;
}

bool BitcoinExchange::getRateForDate(const std::string& date, double& rate) const {
  std::map<std::string,double>::const_iterator it = rates.find(date);
  if (it != rates.end()) { rate = it->second; return true; }
  it = rates.lower_bound(date);
  if (it == rates.begin()) return false;
  if (it == rates.end() || it->first != date) --it;
  rate = it->second;
  return true;
}

void BitcoinExchange::handleLine(const std::string& line) const {
  std::string raw = trim(line);
  if (raw.empty()) return;
  std::size_t sep = raw.find('|');
  if (sep == std::string::npos) {
    std::cout << "Error: bad input => " << raw << std::endl;
    return;
  }
  std::string date = trim(raw.substr(0, sep));
  std::string valueToken = trim(raw.substr(sep + 1));
  if (!validDateFormat(date) || !validDateFields(date)) {
    std::cout << "Error: bad input => " << raw << std::endl;
    return;
  }
  double value;
  if (!parseValue(valueToken, value)) {
    std::cout << "Error: bad input => " << raw << std::endl;
    return;
  }
  if (value < 0) { std::cout << "Error: not a positive number." << std::endl; return; }
  if (value > 1000) { std::cout << "Error: too large a number." << std::endl; return; }
  double rate;
  if (!getRateForDate(date, rate)) {
    std::cout << "Error: bad input => " << raw << std::endl;
    return;
  }
  double result = value * rate;
  std::cout << date << " => " << valueToken << " = " << result << std::endl;
}
