#include "CandlestickMain.h"
#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// Compute candlestick data based on yearly average temperatures
std::vector<Candlestick> computeCandlestickData(const std::string& filename, const std::string& country) {
    auto data = CSVReader::readCSV(filename);
    std::vector<Candlestick> candlesticks;

    std::string currentYear = "";
    double sumTemperatures = 0, maxTemperature = -1e9, minTemperature = 1e9;
    int count = 0;
    double previousClose = 0;

    for (size_t i = 1; i < data.size(); ++i) { // Skip header row
        const auto& row = data[i];
        if (row.size() < 2) continue;

        std::string date = row[0];
        double temperature = std::stod(row[1]);

        std::string year = date.substr(0, 4);
        if (year != currentYear) {
            if (!currentYear.empty()) {
                double open = previousClose;
                double close = sumTemperatures / count;
                candlesticks.push_back(Candlestick(currentYear, open, maxTemperature, minTemperature, close));
                previousClose = close;
            }
            currentYear = year;
            sumTemperatures = 0;
            maxTemperature = -1e9;
            minTemperature = 1e9;
            count = 0;
        }

        sumTemperatures += temperature;
        maxTemperature = std::max(maxTemperature, temperature);
        minTemperature = std::min(minTemperature, temperature);
        count++;
    }

    if (count > 0) {
        double open = previousClose;
        double close = sumTemperatures / count;
        candlesticks.push_back(Candlestick(currentYear, open, maxTemperature, minTemperature, close));
    }

    return candlesticks;
}

// Filter candlestick data by temperature range
std::vector<Candlestick> filterByTemperatureRange(const std::vector<Candlestick>& candlesticks, double minTemp, double maxTemp) {
    std::vector<Candlestick> filtered;

    for (const auto& candle : candlesticks) {
        if (candle.low >= minTemp && candle.high <= maxTemp) {
            filtered.push_back(candle);
        }
    }

    return filtered;
}

// Predict future candlestick data based on trends
std::vector<Candlestick> predictFutureData(const std::vector<Candlestick>& candlesticks, int futureYears) {
    std::vector<Candlestick> predictions;

    if (candlesticks.size() < 2) {
        throw std::runtime_error("Insufficient data for prediction");
    }

    // Calculate linear trends for open, high, low, close
    double trendOpen = candlesticks.back().open - candlesticks[candlesticks.size() - 2].open;
    double trendHigh = candlesticks.back().high - candlesticks[candlesticks.size() - 2].high;
    double trendLow = candlesticks.back().low - candlesticks[candlesticks.size() - 2].low;
    double trendClose = candlesticks.back().close - candlesticks[candlesticks.size() - 2].close;

    std::string lastYear = candlesticks.back().date;
    int year = std::stoi(lastYear);

    for (int i = 1; i <= futureYears; ++i) {
        year++;
        double open = candlesticks.back().open + (trendOpen * i);
        double high = candlesticks.back().high + (trendHigh * i);
        double low = candlesticks.back().low + (trendLow * i);
        double close = candlesticks.back().close + (trendClose * i);

        predictions.push_back(Candlestick(std::to_string(year), open, high, low, close));
    }

    return predictions;
}
