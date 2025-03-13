#include "Candlestick.h"

Candlestick::Candlestick(std::string d, double o, double h, double l, double c)
    : date(d), open(o), high(h), low(l), close(c) {}

void Candlestick::print() const {
    std::cout << std::setw(10) << date << "  "
              << std::setw(10) << std::fixed << std::setprecision(2) << open << "  "
              << std::setw(10) << high << "  "
              << std::setw(10) << low << "  "
              << std::setw(10) << close << std::endl;
}
