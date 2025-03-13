#pragma once
#include "Candlestick.h"
#include <vector>
#include <string>

std::vector<Candlestick> computeCandlestickData(const std::string& filename, const std::string& country);
std::vector<Candlestick> filterByDateRange(const std::vector<Candlestick>& candlesticks, const std::string& startDate, const std::string& endDate);
std::vector<Candlestick> filterByTemperatureRange(const std::vector<Candlestick>& candlesticks, double minTemp, double maxTemp);
std::vector<Candlestick> predictFutureData(const std::vector<Candlestick>& candlesticks, int futureYears);
