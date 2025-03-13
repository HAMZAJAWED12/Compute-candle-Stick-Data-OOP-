#pragma once
#include "CandlestickMain.h"
#include "CandlestickPlot.h"
#include <vector>
#include <string>

class CandlestickMenu {
public:
    CandlestickMenu(const std::string& filename);
    void init();

private:
    void printMenu();
    void processUserOption(int userOption);

    void viewAllCandlesticks();
    void filterByTemperatureRange();
    void predictFutureTrends();

    std::vector<Candlestick> candlesticks;
};
