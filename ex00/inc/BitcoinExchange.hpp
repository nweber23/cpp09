#pragma once

#include <iostream>
#include <map>
#include <exception>
#include <fstream>
#include <sstream>
#include <cstdlib>

class BitcoinExchange {
  public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string& path);
    void processInputFile(const std::string& path) const;
  private:
    std::map<std::string, double> rates;

    static std::string trim(const std::string& s);
    static bool parseValue(const std::string& token, double& out);
    static bool validDateFormat(const std::string& d);
    static bool validDateFields(const std::string& d);
    static bool isLeap(int y);
    bool getRateForDate(const std::string& date, double& rate) const;
    void handleLine(const std::string& line) const;
};