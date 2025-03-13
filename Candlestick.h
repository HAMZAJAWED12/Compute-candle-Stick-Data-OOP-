#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Candlestick {
public:
    std::string date;
    double open;
    double high;
    double low;
    double close;

    Candlestick(std::string d, double o, double h, double l, double c);
    void print() const;
};
