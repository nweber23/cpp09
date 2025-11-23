#pragma once

#include <iostream>
#include <map>
#include <exception>

class BitcoinExchange {
  public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadData(const std::string& filename);
    void processInput(const std::string& filename) const;
  private:
    std::map<std::string, double> data;
    bool isValidDate(const std::string& date) const;
    double getExchangeRate(const std::string& date) const;
    void parseLine(const std::string& line, std::string& date, double& value) const;
};